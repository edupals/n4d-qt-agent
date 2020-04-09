
import os
import subprocess
import time

class Agent:
    def __init__(self):
        pass
    
    def run(self):
        self.ps = subprocess.Popen(("/usr/bin/n4d-qt-agent"),stdout=subprocess.PIPE)
        
    
    def get_ticket(self):
        output = self.ps.communicate()[0]
        
        if (self.ps.returncode!=0):
            return None
        
        tmp=output.split()
        return tmp
        
    def is_running(self):
        return (self.ps.poll()==None)
    
print("running...")
agent=Agent()
agent.run()

while (agent.is_running()):
    time.sleep(1)
    print("waiting...")
    
print(agent.get_ticket())

