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

#ifndef N4D_AGENT_LOGINUI
#define N4D_AGENT_LOGINUI

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>

namespace edupals {
    namespace n4d
    {
        namespace agent
        {
            struct Connection
            {
                QString address;
                int port;
            };
            
            class LoginWindow: public QMainWindow
            {
                Q_OBJECT
                
                public:
                    
                QString user;
                Connection connection;
                
                QLineEdit* editUser;
                QLineEdit* editPass;
                QLineEdit* editServer;
                QLabel* lblError;
                
                LoginWindow(bool showServer,QString defaultAddress,QString message);
                
                protected:
                
                void login();
            };
        }
    }
}

#endif
