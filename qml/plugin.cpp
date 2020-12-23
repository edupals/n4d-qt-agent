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

#include <QQmlExtensionPlugin>
#include <QObject>
#include <QQmlEngine>
#include <QAbstractItemModel>
#include <QMimeData>
#include <QThread>

#include <iostream>
#include <chrono>

using namespace std;
using namespace edupals;

Proxy::Proxy() : QObject(nullptr) 
{
    system::User me = system::User::me();
    
    m_userName=QString::fromStdString(me.name);
    emit userNameChanged();
    
}

void Proxy::requestTicket(QString address,int port,QString user,QString password)
{
    clog<<"requestTicket"<<endl;
    
    QThread* worker = QThread::create([=]() {
        emit ticket(0,QLatin1String("All your base are belong to us"));
    });
    
    worker->start();
}

AgentPlugin::AgentPlugin(QObject* parent) : QQmlExtensionPlugin(parent)
{
}

void AgentPlugin::registerTypes(const char* uri)
{
    qmlRegisterType<Proxy> (uri, 1, 0, "Proxy");
    qmlRegisterAnonymousType<QMimeData>(uri, 1);
    
}
