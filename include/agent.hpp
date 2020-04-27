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
#include <vector>

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
            
            enum class State
            {
                NotReady,
                Success,
                Error
            };
            
            class Ticket
            {
                public:
                
                State status;
                auth::Credential credential;
                std::string address;
                int port;
                
                /*!
                 * Whenever the ticket status is Succes or not
                */
                bool valid();
            };
            
            class LoginDialog
            {
                protected:
                
                Ticket ticket;
                system::Process child;
                int status;
                int rpipe [2];
                std::vector<std::string> cmdline;
                
                std::vector<std::string> split(std::string in);
                void compute_ticket();
                
                public:
                
                /*!
                 * Default constructor, no welcome message and addressed to localhost
                */
                LoginDialog();
                
                /*!
                 * Constructor with custom message
                 */
                LoginDialog(std::string message);
                
                /*!
                 * Constructor with custom message and custom address
                 * \param message welcome message
                 * \param address default n4d address
                 * \param show_server whenever allow user to view/change server
                */
                LoginDialog(std::string message,std::string address,bool show_server);
                
                /*!
                 * launch dialog, non-blocking
                */
                void run();
                
                /*!
                 * returns true if the dialog already finished, with either success or not. Non-blocking.
                */
                bool ready();
                
                /*!
                 * Gets the ticket. The ticket may be NotReady, Succes or Error but will always return a Ticket, so it must be checked. Non-blocking.
                */
                Ticket value();
            };
        }
    }
}

#endif
