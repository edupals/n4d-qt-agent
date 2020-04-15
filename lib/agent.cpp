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
using namespace std;

Agent::Agent()
{
}

void Agent::run()
{
    char* args[]={"/usr/bin/n4d-qt-agent",nullptr};
    
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
        clog<<"pid:"<<pid<<endl;
        close(rpipe[1]);
        child = system::Process(pid);
    }
}

bool Agent::is_running()
{
    int status;
    pid_t pid = waitpid(child.pid(),&status,WNOHANG);
    
    return (pid==0);
}

string Agent::get_ticket()
{

    char buffer[1024];
    size_t nbytes;
    
    nbytes=read(rpipe[0],buffer,1024);
    
    if (nbytes>0) {
        return string(buffer,nbytes);
    }
    else {
        return "none";
    }
}
