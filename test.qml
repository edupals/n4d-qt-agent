import QtQuick 2.6
import Edupals.N4D.Agent 1.0 as N4DAgent

Rectangle
{
    width: 450
    height: 250
    
    N4DAgent.Login
    {
        showServer: true
        //server: "https://localhost"
        //user: "netadmin"
        showCancel: false
        
        anchors.centerIn: parent
        
        onLogged: {
            console.log(ticket);
        }
    }
}