
import n4d.agent
import os
import time

if __name__=="__main__":
    print("running...")
    dialog=n4d.agent.LoginDialog()
    dialog.run()

    while (not dialog.ready()):
        time.sleep(1)
        print("waiting...")
        
    print(dialog.value())

