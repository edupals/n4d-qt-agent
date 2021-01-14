import QtQuick 2.6
import Edupals.N4D.Agent 1.0 as N4DAgent

Rectangle
{
    width: loginWidget.width
    height: loginWidget.height
    
    N4DAgent.Login
    {
        id: loginWidget
        
        showAddress: true
        //address: "https://localhost:9779"
        //user: "netadmin"
        showCancel: true
        //trustLocal: true
        
        anchors.centerIn: parent
        
        onLogged: {
            console.log(ticket);
        }
    }
}
