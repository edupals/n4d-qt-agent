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
#include <user.hpp>

#include <QCoreApplication>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QUrl>

#include <iostream>

using namespace edupals;
using namespace edupals::n4d;
using namespace edupals::n4d::agent;
using namespace std;

static Connection parseUrl(QString inAddress)
{
    Connection ret;
    
    QUrl url(inAddress);
    
    QString tmpAddress=url.host();
    QString tmpAddres2=url.url();
    int tmpPort=url.port();
    
    if (tmpPort==-1) {
        tmpPort=9779;
    }
    
    if (tmpAddress.size()==0) {
        if (tmpAddres2.size()==0) {
            QCoreApplication::exit(2);
        }
        else {
            tmpAddress=tmpAddres2;
        }
    }
    
    ret.address="https://"+tmpAddress;
    ret.port=tmpPort;
    
    return ret;
}

LoginWindow::LoginWindow(bool showServer,QString defaultAddress, QString message) : QQuickView()
{
    locale::domain("n4d-qt-agent");
    
    //connection = parseUrl(defaultAddress);
    
    system::User user = system::User::me();
    /*
    setWindowTitle("N4D login");
    setWindowIcon(QIcon::fromTheme("avatar-default-symbolic"));
    setFixedSize(QSize(300, 210));
    setWindowFlags(Qt::Dialog);
    */
    setSource(QUrl(QStringLiteral("qrc:/login.qml")));
    
}

void LoginWindow::login()
{
    
}
