/*
 * Copyright (C) 2024 Lliurex project
 *
 * Author:
 *  Enrique Medina Gremaldos <quique@necos.es>
 *
 * Source:
 *  https://github.com/edupals/qml-module-edupals-n4d
 *
 * This file is a part of qml-module-edupals-n4d.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 */

#include "plugin.h"

#include <user.hpp>
#include <n4d.hpp>
#include <variant.hpp>

#include <systemd/sd-journal.h>

#include <QQmlExtensionPlugin>
#include <QQmlEngine>
#include <QObject>
#include <QAbstractItemModel>
#include <QMimeData>
#include <QThread>
#include <QUrl>
#include <QDebug>

#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace edupals;

static bool inGroups(n4d::Client& client,QVariantList groups)
{
    
    vector<string> userGroups = client.get_groups();
    
    for (int n=0;n<groups.size();n++) {
        QVariant tmp = groups.at(n);
        string name = tmp.value<QString>().toStdString();
        
        for (string ug : userGroups) {
            if (ug==name) {
                return true;
            }
        }
        
    }
    
    return false;
}

Proxy::Proxy() : QObject(nullptr) 
{
    system::User me = system::User::me();
    
    m_userName=QString::fromStdString(me.name);
    emit userNameChanged();
    
}

static int completeURL(QString& address)
{
    QUrl url(address);
    QUrl nurl;
    
    if (!url.isValid()) {
        return -1;
    }
    
    if (url.scheme().length()==0) {
        nurl.setScheme(QLatin1String("https"));
    }
    else {
        nurl.setScheme(url.scheme());
    }
    
    if (url.port()==-1) {
        nurl.setPort(9779);
    }
    else {
        nurl.setPort(url.port());
    }
    
    if (url.host().length()==0) {
        if (url.path().length()>0) {
            nurl.setHost(url.path());
        }
        else {
            return -1;
        }
    }
    else {
        nurl.setHost(url.host());
    }
    
    address = nurl.toString();
    
    return 0;
}

void Proxy::requestTicket(QString address,QString user,QString password, QVariantList groups)
{
    completeURL(address);
    sd_journal_print(LOG_INFO,"requesting a remote ticket to %s",address.toLocal8Bit().constData());
    
    QThread* worker = QThread::create([=]() {
        
        n4d::Client client(address.toStdString(),user.toStdString(),password.toStdString());
        
        try {
            n4d::Ticket utk = client.get_ticket();
            
            if (utk.valid()) {
                
                if (groups.size()>0) {
                    n4d::Client gclient(utk);
                    
                    if (!inGroups(gclient,groups)) {
                        emit ticket(Status::InvalidUserGroup,QLatin1String(""));
                        sd_journal_print(LOG_ERR,"user is not in a valid group");
                        return;
                    }
                }
                
                QString n4dticket = QString::fromStdString(utk.to_string());
                
                emit ticket(Status::CallSuccessful,n4dticket);
            }
            else {
                sd_journal_print(LOG_ERR,"invalid key");
                emit ticket(Status::InvalidKey,QLatin1String(""));
            }
        }
        catch(n4d::exception::AuthenticationFailed& e) {
            sd_journal_print(LOG_ERR,"authentication failed");
            emit ticket(Status::AuthenticationFailed,QLatin1String(""));
        }
        catch(n4d::exception::InvalidServerResponse& e) {
            sd_journal_print(LOG_ERR,"invalid server response:%s",e.what());
            emit ticket(Status::InvalidServerResponse,QLatin1String(""));
        }
        catch (std::exception& e) {
            sd_journal_print(LOG_ERR,e.what());
            emit ticket(Status::UnknownError,QLatin1String(""));
        }
    });
    
    worker->start();
}

void Proxy::requestLocalTicket(QString user, QVariantList groups)
{
    sd_journal_print(LOG_INFO,"requesting local ticket...");
    
    n4d::auth::Key userKey = n4d::auth::Key::user_key(user.toStdString());
    
    if (userKey.valid()) {
        sd_journal_print(LOG_INFO,"found a local ticket");
        
        n4d::Ticket utk("https://127.0.0.1:9779",n4d::auth::Credential(user.toStdString(),userKey));
        
        //checking groups
        if (groups.size()>0) {
            
            n4d::Client gclient(utk);
            
            if (!inGroups(gclient,groups)) {
                emit ticket(Status::InvalidUserGroup,QLatin1String(""));
                sd_journal_print(LOG_ERR,"user is not in a valid group");
                return;
            }
        }
        
        QString n4dticket = QString::fromStdString(utk.to_string());
        emit ticket(Status::CallSuccessful,n4dticket);
    }
    else {
        sd_journal_print(LOG_INFO,"no local ticket found, requesting one...");
        
        QThread* worker = QThread::create([=]() {
            
            n4d::Client client("https://127.0.0.1:9779",user.toStdString(),"");
            
            try {
                n4d::Ticket utk = client.create_ticket();
                
                if (utk.valid()) {
                    
                    //checking groups
                    if (groups.size()>0) {
                        
                        n4d::Client gclient(utk);
                        
                        if (!inGroups(gclient,groups)) {
                            emit ticket(Status::InvalidUserGroup,QLatin1String(""));
                            sd_journal_print(LOG_ERR,"user is not in a valid group");
                            return;
                        }
                    }
                    
                    QString n4dticket = QString::fromStdString(utk.to_string());
                    
                    emit ticket(Status::CallSuccessful,n4dticket);
                }
                else {
                    sd_journal_print(LOG_ERR,"invalid key");
                    emit ticket(Status::InvalidKey,QLatin1String(""));
                }
            }
            catch(std::exception& e) {
                qDebug()<<e.what();
                emit ticket(Status::UnknownError,QLatin1String(""));
            }
            
        });
        
        worker->start();
    }
}

AgentPlugin::AgentPlugin(QObject* parent) : QQmlExtensionPlugin(parent)
{
}

void AgentPlugin::registerTypes(const char* uri)
{
    qmlRegisterType<Status> (uri, 1, 0, "Status");
    qmlRegisterType<Proxy> (uri, 1, 0, "Proxy");
    qmlRegisterAnonymousType<QMimeData>(uri, 1);
    
}
