
import os
import subprocess
import time

class N4DAgent:
    def __init__(self):
        pass
    
    def run(self):
        self.ps = subprocess.Popen(("/usr/bin/n4d-qt-agent"),stdout=subprocess.PIPE)
        
    
    def wait(self):
        output = self.ps.communicate()[0]
        print("return code:{0}".format(self.ps.returncode))
        print(output)
        
    def is_running(self):
        return (self.ps.poll()==None)
    
print("running...")
agent=N4DAgent()
agent.run()

while (agent.is_running()):
    time.sleep(1)
    print("tick")
    
agent.wait()
print("done")
