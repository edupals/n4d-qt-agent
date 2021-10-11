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

#include <QQuickView>

namespace edupals 
{
    namespace n4d
    {
        namespace agent
        {
            class Bridge: public QObject
            {
                Q_OBJECT
                
                Q_PROPERTY(QString defaultAddress MEMBER m_defaultAddress CONSTANT)
                Q_PROPERTY(bool showAddress MEMBER m_showAddress CONSTANT)
                Q_PROPERTY(QString message MEMBER m_message CONSTANT)
                
                public:
                
                Bridge(QString defaultAddress,bool showAddress,QString message) :
                    m_defaultAddress(defaultAddress), m_showAddress(showAddress), m_message(message) 
                {
                    
                }
                
                QString m_defaultAddress;
                bool m_showAddress;
                QString m_message;
                
                Q_SIGNALS:
                
                void logged(QString ticket);
                void canceled();
                
            };

            class LoginWindow: public QQuickView
            {
                Q_OBJECT
                
                public:
                
                LoginWindow(QString defaultAddress,bool showAddress,QString message);
                
            };
        }
    }
}

#endif
