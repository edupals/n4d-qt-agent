/*
 * Copyright (C) 2020 Lliurex project
 *
 * Author:
 *  Enrique Medina Gremaldos <quiqueiii@gmail.com>
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

#include <QQmlExtensionPlugin>
#include <QQmlEngine>
#include <QObject>
#include <QAbstractItemModel>
#include <QMimeData>
#include <QThread>
#include <QUrl>
#include <QDebug>

#include <iostream>

using namespace std;
using namespace edupals;

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
    
    if (url.scheme().count()==0) {
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
    
    if (url.host().count()==0) {
        if (url.path().count()>0) {
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

void Proxy::requestTicket(QString address,QString user,QString password)
{
    completeURL(address);
    qDebug()<<"requesting remote ticket to "<<address;
    
    QThread* worker = QThread::create([=]() {
        
        n4d::Client client(address.toStdString(),user.toStdString(),password.toStdString());
        
        try {
            n4d::auth::Credential credential = client.get_ticket();
            
            if (credential.key) {
                QLatin1String sep(" ");
                QString n4dticket = QLatin1String("N4DTKV2")+sep+address+sep+user+sep+QString::fromStdString(credential.key.value);
                
                qDebug()<<n4dticket;
                
                emit ticket(Status::CallSuccessful,n4dticket);
            }
            else {
                qDebug()<<"Invalid key:"<<QString::fromStdString(credential.key.value);
                emit ticket(Status::InvalidKey,QLatin1String(""));
            }
        }
        catch(n4d::exception::AuthenticationFailed& e) {
            qDebug()<<"Authentication Failed";
            emit ticket(Status::AuthenticationFailed,QLatin1String(""));
        }
        catch(n4d::exception::InvalidServerResponse& e) {
            qDebug()<<e.what();
            emit ticket(Status::InvalidServerResponse,QLatin1String(""));
        }
        catch (std::exception& e) {
            qDebug()<<e.what();
            emit ticket(Status::UnknownError,QLatin1String(""));
        }
    });
    
    worker->start();
}

void Proxy::requestLocalTicket(QString user)
{
    qDebug()<<"requesting local ticket...";
    
    n4d::auth::Key userKey = n4d::auth::Key::user_key(user.toStdString());
    
    if (userKey.valid()) {
        qDebug()<<"found a local ticket";
        
        QLatin1String sep(" ");
        QString n4dticket = QLatin1String("N4DTKV2 https://127.0.0.1:9779")+sep+user+sep+QString::fromStdString(userKey.value);
        emit ticket(Status::CallSuccessful,n4dticket);
    }
    else {
        qDebug()<<"no local ticket found, requesting one...";
        
        QThread* worker = QThread::create([=]() {
            
            n4d::Client client("https://127.0.0.1:9779",user.toStdString(),"");
            
            try {
                n4d::auth::Credential credential = client.create_ticket();
                
                if (credential.key) {
                    
                    QLatin1String sep(" ");
                    QString n4dticket = QLatin1String("N4DTKV2 https://127.0.0.1:9779")+sep+user+sep+QString::fromStdString(credential.key.value);
                    
                    qDebug()<<n4dticket;
                    emit ticket(Status::CallSuccessful,n4dticket);
                }
                else {
                    qDebug()<<"Invalid key:"<<QString::fromStdString(credential.key.value);
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
