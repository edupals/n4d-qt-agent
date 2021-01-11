/*
 * Copyright (C) 2020 Lliurex project
 *
 * Author:
 *  Enrique Medina Gremaldos <quiqueiii@gmail.com>
 *
 * Source:
 *  https://github.com/edupals/n4d-qt-agent
 *
 * This file is a part of n4d-qt-agent
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

#ifndef QML_EDUPALS_N4D_AGENT_PLUGIN
#define QML_EDUPALS_N4D_AGENT_PLUGIN

#include <QQmlExtensionPlugin>
#include <QObject>

class Status: public QObject
{
    Q_OBJECT
    
    public:
        
    enum StatusCode
    {
        CallSuccessful = 0,
        AuthenticationFailed = -10,
        InvalidServerResponse = -1001,
        UnknownError = -2000,
        InvalidKey = -2001
    };
        
    Q_ENUM(StatusCode)
    
};

class Proxy: public QObject
{
    Q_OBJECT
    
    Q_PROPERTY(QString userName MEMBER m_userName NOTIFY userNameChanged READ getUserName)
    
    public:
    
    QString m_userName;
    
    Proxy();
    
    QString getUserName()
    {
        return m_userName;
    }
    
    Q_INVOKABLE void requestTicket(QString address,QString user,QString password);
    Q_INVOKABLE void requestLocalTicket(QString user);
    
    Q_SIGNALS:
    
    void userNameChanged();
    
    void ticket(int status,QString value);
};

class AgentPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA (IID "Edupals N4D Agent")

public:
    explicit AgentPlugin(QObject *parent = nullptr);
    void registerTypes(const char *uri) override;
};


#endif
