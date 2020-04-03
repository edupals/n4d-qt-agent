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

#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

#include <iostream>

using namespace n4d::agent;
using namespace std;

LoginWindow::LoginWindow(bool showServer) : QMainWindow()
{
    setWindowTitle("N4D login");
    setWindowIcon(QIcon::fromTheme("changes-prevent"));
    setFixedSize(QSize(300, 150));
    setWindowFlags(Qt::Dialog);
    
    QFrame* mainFrame = new QFrame(this);
    QGridLayout* mainLayout = new QGridLayout();
    mainFrame->setLayout(mainLayout);
    setCentralWidget(mainFrame);
    
    editUser = new QLineEdit();
    QLabel* lbl = new QLabel();
    QIcon icon=QIcon::fromTheme("avatar-default-symbolic");
    lbl->setPixmap(icon.pixmap(22,22));
    
    mainLayout->addWidget(lbl,0,0);
    mainLayout->addWidget(new QLabel("User"),0,1);
    mainLayout->addWidget(editUser,0,2);
    
    editPass = new QLineEdit();
    editPass->setEchoMode(QLineEdit::Password);
    lbl = new QLabel();
    icon=QIcon::fromTheme("dialog-password-symbolic");
    lbl->setPixmap(icon.pixmap(22,22));
    
    mainLayout->addWidget(lbl,1,0);
    mainLayout->addWidget(new QLabel("Password"),1,1);
    mainLayout->addWidget(editPass,1,2);
    
    if (showServer) {
        editServer = new QLineEdit("https://localhost:9779");
        lbl = new QLabel();
        icon=QIcon::fromTheme("emblem-system-symbolic");
        lbl->setPixmap(icon.pixmap(22,22));
        
        mainLayout->addWidget(lbl,2,0);
        mainLayout->addWidget(new QLabel("Server"),2,1);
        mainLayout->addWidget(editServer,2,2);
    }
    
    QDialogButtonBox* buttonBox = new QDialogButtonBox();
    QAbstractButton* btnClose;
    QAbstractButton* btnAction;
    btnClose=buttonBox->addButton(QDialogButtonBox::Close);
    btnAction=buttonBox->addButton("login",QDialogButtonBox::ActionRole);
    
    mainLayout->addWidget(buttonBox,(showServer ? 3:2),2);
    
    connect(buttonBox,&QDialogButtonBox::clicked, [=](QAbstractButton* button) {
        
        if (button==btnClose) {
            this->close();
        }
        
        if (button==btnAction) {
            qDebug()<<"login...";
        }
        
    });
    
    show();
}
