import QtQuick 2.6
import Edupals.N4D.Agent 1.0 as N4DAgent


Rectangle {
    width: 600
    height: 400
    anchors.centerIn: parent
    color: "#e9e9e9"

    N4DAgent.Login
    {
        showAddress: true
        address: "https://localhost:9779"
        showCancel: false
        
        anchors.centerIn: parent
        
        onLogged: {
            tunnel.on_ticket(ticket);
        }
    }
}
