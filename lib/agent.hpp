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

#ifndef N4D_AGENT_LIB
#define N4D_AGENT_LIB

#include <process.hpp>
#include <n4d.hpp>

#include <string>
#include <exception>

namespace edupals
{
    namespace n4d
    {
        namespace agent
        {
            namespace exception
            {
                class SpawnError : public std::exception
                {
                    public:
                    
                    const char* what() const throw()
                    {
                        return "Failed to spawn N4D Qt agent";
                    }
                };
            }
            
            class LoginDialog
            {
                protected:
                
                system::Process child;
                int status;
                int rpipe [2];
                
                public:
                
                LoginDialog();
                //LoginDialog(std::string message,std::string address,bool show_server);
                
                void run();
                bool ready();
                auth::Credential value();
            };
        }
    }
}

#endif
