import QtQuick
import QtQuick.Controls as QQC2
import Edupals.N4D.Agent as N4DAgent

QQC2.Pane
{
    anchors.fill:parent
    
    N4DAgent.Login
    {
        showAddress: bridge.showAddress
        address: bridge.defaultAddress
        
        anchors.centerIn: parent
        
        onLogged: {
            bridge.logged(ticket);
        }
        
        onCanceled: {
            bridge.canceled();
        }
    }
}
