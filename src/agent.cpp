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

#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>

using namespace edupals::n4d::agent;
using namespace std;

int main(int argc,char* argv[])
{
    
    QApplication app(argc,argv);
    QApplication::setApplicationName("n4d-qt-agent");
    QApplication::setApplicationVersion("1.0");
    
    QCommandLineParser parser;
    parser.setApplicationDescription("N4D Qt login agent");
    parser.addHelpOption();
    parser.addVersionOption();
    
    QStringList list = {"s","show-server"};
    QCommandLineOption optShowServer(list,"let user select a server");
    parser.addOption(optShowServer);
    
    list = QStringList({"m","message"});
    QCommandLineOption optMessage(list,"add a custom message","message","");
    parser.addOption(optMessage);
    
    list = QStringList({"a","address"});
    QCommandLineOption optAddress(list,"set a custom n4d server address","address","https://localhost:9779");
    parser.addOption(optAddress);

    parser.process(app);
    
    QString message="";
    
    if (parser.isSet(optMessage)) {
        message = parser.value(optMessage); 
    }
    
    QString address = parser.value(optAddress);
    
    LoginWindow win(parser.isSet(optShowServer), address, message);
    win.show();
    
    return app.exec();
}
