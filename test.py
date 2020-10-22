
import os
import subprocess
import time

class LoginDialog:
    
    def __init__(self,message="",address="",show_server=False):
        self.ticket=None
        
        self.cmdline=["/usr/bin/n4d-qt-agent"]
        
        if (message!=""):
            self.cmdline.append("-m")
            self.cmdline.append(message)
        
        if (address!=""):
            self.cmdline.append("-a")
            self.cmdline.append(address)
        
        if (show_server):
            self.cmdline.append("-s")
    
    def run(self):
        self.ticket=None
        self.ps = subprocess.Popen(self.cmdline,stdout=subprocess.PIPE)
    
    def ready(self):
        return (self.ps.poll()!=None)
    
    def value(self):
        
        if (not self.ready()):
            return None
        
        if (self.ticket==None):
            output = self.ps.communicate()[0]
        
            if (self.ps.returncode!=0):
                self.ticket=[False]
            else:
                tmp=output.split()
                if (len(tmp)>=4):
                    self.ticket=[True,str(tmp[0]),str(tmp[1]),str(tmp[2]),int(tmp[3])]
                else:
                    self.ticket=[False]
        
        return self.ticket
        
if __name__=="__main__":
    print("running...")
    dialog=LoginDialog()
    dialog.run()

    while (not dialog.ready()):
        time.sleep(1)
        print("waiting...")
        
    print(dialog.value())

