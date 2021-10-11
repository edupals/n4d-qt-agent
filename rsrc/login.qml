import QtQuick 2.6
import QtQuick.Controls 2.6 as QQC2
import Edupals.N4D.Agent 1.0 as N4DAgent

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
