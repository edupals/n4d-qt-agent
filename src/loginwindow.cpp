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
#include <QPushButton>
#include <QLabel>

#include <iostream>

using namespace n4d::agent;
using namespace std;

LoginWindow::LoginWindow() : QMainWindow()
{
    setWindowTitle("N4D login");
    setWindowIcon(QIcon::fromTheme("document-decrypt"));
    setFixedSize(QSize(400, 300));
    setWindowFlags(Qt::Dialog);
    
    QFrame* mainFrame = new QFrame(this);
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainFrame->setLayout(mainLayout);
    setCentralWidget(mainFrame);
    
    QDialogButtonBox* buttonBox = new QDialogButtonBox();
    QAbstractButton* btnClose;
    QAbstractButton* btnAction;
    btnClose=buttonBox->addButton(QDialogButtonBox::Close);
    btnAction=buttonBox->addButton("login",QDialogButtonBox::ActionRole);
    
    mainLayout->addWidget(buttonBox);
    
    show();
}
