/*
    N4D Qt agent

    Copyright (C) 2020  Enrique Medina Gremaldos <quiqueiii@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "loginwindow.hpp"
#include "locale.hpp"

#include <n4d.hpp>

#include <QQmlContext>
#include <QCoreApplication>
#include <QDebug>

#include <iostream>

using namespace edupals;
using namespace edupals::n4d;
using namespace edupals::n4d::agent;
using namespace std;

LoginWindow::LoginWindow(QString defaultAddress, bool showAddress, QString message) : QQuickView()
{
    
    setTitle("N4D login");
    setIcon(QIcon::fromTheme("avatar-default-symbolic"));
    setMaximumSize(QSize(460, 260));
    setMinimumSize(QSize(460, 260));
    setFlags(Qt::Dialog);
    
    QQmlContext* ctxt = rootContext();
    
    Bridge* bridge = new Bridge(defaultAddress,showAddress,message);
    
    connect(bridge,&Bridge::logged, [](QString ticket) {
            cout<<ticket.toStdString()<<endl;
        });
    
    connect(bridge,&Bridge::canceled, []() {
            QCoreApplication::exit(1);
        });
    
    ctxt->setContextProperty(QStringLiteral("bridge"),bridge);
    setSource(QUrl(QStringLiteral("qrc:/login.qml")));
    
}
