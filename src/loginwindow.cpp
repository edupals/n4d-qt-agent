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

LoginWindow::LoginWindow(bool showServer,QString defaultAddress, QString message) : QMainWindow()
{
    locale::domain("n4d-qt-agent");
    
    connection = parseUrl(defaultAddress);
    
    system::User user = system::User::me();
    
    setWindowTitle("N4D login");
    setWindowIcon(QIcon::fromTheme("avatar-default-symbolic"));
    setFixedSize(QSize(300, 210));
    setWindowFlags(Qt::Dialog);
    
    QFrame* mainFrame = new QFrame(this);
    QGridLayout* mainLayout = new QGridLayout();
    mainFrame->setLayout(mainLayout);
    setCentralWidget(mainFrame);
    
    QLabel* lblMessage = new QLabel(message);
    mainLayout->addWidget(lblMessage,0,1,1,-1, Qt::AlignHCenter);
    
    editUser = new QLineEdit(user.name.c_str());
    QLabel* lbl = new QLabel();
    QIcon icon=QIcon::fromTheme("avatar-default-symbolic");
    lbl->setPixmap(icon.pixmap(22,22));
    
    mainLayout->addWidget(lbl,1,0);
    mainLayout->addWidget(new QLabel("User"),1,1);
    mainLayout->addWidget(editUser,1,2);
    
    editPass = new QLineEdit();
    editPass->setEchoMode(QLineEdit::Password);
    lbl = new QLabel();
    icon=QIcon::fromTheme("dialog-password-symbolic");
    lbl->setPixmap(icon.pixmap(22,22));
    connect(editPass,&QLineEdit::returnPressed,[=](){
    
        login();
    });
    
    mainLayout->addWidget(lbl,2,0);
    mainLayout->addWidget(new QLabel("Password"),2,1);
    mainLayout->addWidget(editPass,2,2);
    
    if (showServer) {
        editServer = new QLineEdit(connection.address+":"+QString::number(connection.port));
        lbl = new QLabel();
        icon=QIcon::fromTheme("emblem-system-symbolic");
        lbl->setPixmap(icon.pixmap(22,22));
        
        mainLayout->addWidget(lbl,3,0);
        mainLayout->addWidget(new QLabel("Server"),3,1);
        mainLayout->addWidget(editServer,3,2);
    }
    
    lblError = new QLabel("");
    mainLayout->addWidget(lblError,4,1,1,-1,Qt::AlignHCenter);
    
    QDialogButtonBox* buttonBox = new QDialogButtonBox();
    QAbstractButton* btnClose;
    QAbstractButton* btnAction;
    btnClose=buttonBox->addButton(QDialogButtonBox::Close);
    btnAction=buttonBox->addButton(locale::T("login"),QDialogButtonBox::ActionRole);
    
    mainLayout->addWidget(buttonBox,5,2);
    
    connect(buttonBox,&QDialogButtonBox::clicked, [=](QAbstractButton* button) {
        
        if (button==btnClose) {
            QCoreApplication::exit(1);
        }
        
        if (button==btnAction) {
            
            if (showServer) {
                connection = parseUrl(editServer->text());
            }
            
            login();
        }
    });
    
    show();
}

void LoginWindow::login()
{
    std::string user = editUser->text().toStdString();
    std::string password = editPass->text().toStdString();
    
    Client client(connection.address.toStdString(),connection.port);
    clog<<"Connecting to "<<connection.address.toStdString()<<":"<<connection.port<<endl;
    //client.set_flags(n4d::Option::Verbose);
    
    auth::Credential login(user,password);
    
    try {
        variant::Variant value = client.call("NTicketsManager","get_ticket",{login.user},login);

        string ticket = value.get_string();

        //Ok, this really has some room for improvement
        bool fail=false;

        if (ticket=="USER AND/OR PASSWORD ERROR") {
            fail=true;
        } else {
            if (ticket=="USER DOES NOT EXIST") {
                fail=true;
            }
        }

        if (fail) {
            lblError->setStyleSheet("QLabel{color: red}");
            lblError->setText(locale::T("Bad user/password"));
        }
        else {
            //dump user and ticket to standard output
            cout<<user<<" "<<value.get_string()<<endl;
            QCoreApplication::exit(0);
        }
    }
    catch(std::exception& e) {
        lblError->setStyleSheet("QLabel{color: red}");
        lblError->setText(locale::T("Failed to connect N4D server"));

        cerr<<e.what()<<endl;
    }
    
}
