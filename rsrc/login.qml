import QtQuick 2.6
import Edupals.N4D.Agent 1.0 as N4DAgent

Rectangle
{
    width: 450
    height: 250
    
    N4DAgent.Login
    {
        showAddress: bridge.showAddress
        address: bridge.defaultAddress
        
        anchors.centerIn: parent
        
        onLogged: {
            bridge.logged(ticket);
        }
    }
}
