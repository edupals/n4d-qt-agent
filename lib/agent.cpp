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

#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

using namespace edupals::n4d;
using namespace edupals::n4d::agent;
using namespace std;

bool Ticket::valid()
{
    return (status==State::Success);
}

vector<string> LoginDialog::split(string in)
{
    vector<string> ret;
    string tmp;
    
    for (char c:in) {
        
        if (c==' ') {
            ret.push_back(tmp);
            tmp="";
        }
        else {
            tmp=tmp+c;
        }
    }
    
    if (tmp.size()>0) {
        ret.push_back(tmp);
    }
    
    return ret;
}

void LoginDialog::compute_ticket()
{
    char buffer[1024];
    size_t nbytes;
    
    nbytes=read(rpipe[0],buffer,1024);
    
    if (nbytes>0) {
        string in(buffer,nbytes);
        close(rpipe[0]);

        vector<string> values = split(in);
        
        if (values.size()==4) {
            string user = values[0];
            string key = values[1];
            string address = values[2];
            string port_s = values[3];
            
            int port = stoi(port_s);
            
            ticket.credential = auth::Credential(user,auth::Key(key));
            ticket.address = address;
            ticket.port = port;
            ticket.status = State::Success;
        }
    }
}

LoginDialog::LoginDialog()
{
    cmdline.push_back("/usr/bin/n4d-qt-agent");
}

LoginDialog::LoginDialog(string message) : LoginDialog()
{
    cmdline.push_back("-m");
    cmdline.push_back(message);
}

LoginDialog::LoginDialog(string message,string address,bool show_server) : LoginDialog()
{
    cmdline.push_back("-m");
    cmdline.push_back(message);
    
    cmdline.push_back("-a");
    cmdline.push_back(address);
    
    if (show_server) {
        cmdline.push_back("-s");
    }
}

void LoginDialog::run()
{
    ticket.status=State::NotReady;
    ticket.credential=auth::Credential();
    status=0;
    
    //char* args[]={"/usr/bin/n4d-qt-agent",nullptr};
    char* args[32];
    int n=0;
    
    for (string& s:cmdline) {
        args[n]=( char*)s.c_str();
        n++;
    }
    args[n]=0;
    
    pipe(rpipe);
    
    pid_t pid = fork();
    
    if (pid==-1) {
        throw exception::SpawnError();
    }
    
    if (pid==0) {
        
        close(rpipe[0]);
        
        dup2(rpipe[1],1); //stdout
        
        close(rpipe[1]);
        
        execv("/usr/bin/n4d-qt-agent",args);
        exit(0);
    }
    else {
        close(rpipe[1]);
        child = system::Process(pid);
    }
}

bool LoginDialog::ready()
{
    pid_t pid = waitpid(child.pid(),&status,WNOHANG);
    return (pid!=0);
}

Ticket LoginDialog::value()
{
    
    if (ticket.status==State::NotReady) {
        if (ready()) {
            if (WIFEXITED(status)!=0) {
                if (WEXITSTATUS(status)!=0) {
                    ticket.status=State::Error;
                }
                else {
                    compute_ticket();
                    ticket.status=State::Success;
                }
            }
        }
    }
    
    return ticket;
}
