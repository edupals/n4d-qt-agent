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

#include "agent.hpp"

#include <iostream>
#include <chrono>
#include <thread>

using namespace edupals::n4d;
using namespace edupals::n4d::agent;
using namespace std;

int main(int argc,char* argv[])
{
    LoginDialog dialog;
    
    dialog.run();
    
    while (!dialog.ready()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    
    auth::Credential cred = dialog.value();
    
    cout<<"user:["<<cred.user<<"]"<<endl;
    cout<<"key:["<<cred.key<<"]"<<endl;
    
    return 0;
}
