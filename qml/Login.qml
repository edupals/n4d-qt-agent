
import Edupals.N4D.Agent 1.0 as N4DAgent

import QtQuick 2.6
import QtQuick.Layouts 1.1 as Layouts
import QtQuick.Controls 2.6 as QQC2
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.kirigami 2.5 as Kirigami

QQC2.StackView {
    id: root
    width: 400
    height: 240
    
    initialItem: firstPage
    
    property alias message: labelCustomMessage.text
    property alias address: addressField.text
    property alias user: userField.text
    property alias showAddress: rowAddress.visible
    property alias showCancel: btnCancel.visible
    property bool trustLocal: false
    
    
    signal logged(var ticket)
    signal canceled()
    signal failed(int code,string what)
    
    N4DAgent.Proxy {
        id: n4dAgent
    }
    
    Connections {
        target: n4dAgent
        
        function onTicket(code,value) {
            //btnLogin.enabled=true;
            firstPage.enabled=true;
            if (code==N4DAgent.Status.CallSuccessful) {
                root.push(secondPage);
                root.logged(value);
            }
            else {
                passwordField.text="";
                errorLabel.text="Error "+code;
                errorLabel.visible=true;
            
                root.failed(code,value);
            }
        }
    }
    
    Component.onCompleted: {
        if (trustLocal) {
            n4dAgent.requestLocalTicket(n4dAgent.userName);
        }
    }
    
    MouseArea {
        cursorShape: firstPage.enabled==false ? Qt.BusyCursor : Qt.ArrowCursor
        anchors.fill: parent
    }
    
    QQC2.Pane {
        id: firstPage
        width: 400
        height: 240
        
        Column {
            anchors.fill:parent
            
            spacing: units.smallSpacing
            
            QQC2.Label {
                
                id: labelCustomMessage
                text: "Put N4D credentials"
            }
            
            Row {
                id: rowAddress
                anchors.right: rowUser.right
                topPadding: units.smallSpacing
                spacing: units.smallSpacing
                visible: false
                
                QQC2.Label {
                    text:i18nd("n4d-qt-agent","Address")
                    anchors.verticalCenter: addressField.verticalCenter
                }
                
                QQC2.TextField {
                    id: addressField
                    text: "localhost"
                }
            }
            
            Row {
                id: rowUser
                spacing: units.smallSpacing
                anchors.horizontalCenter:parent.horizontalCenter
                
                QQC2.Label {
                    text:i18nd("n4d-qt-agent","User")
                    anchors.verticalCenter: userField.verticalCenter
                }
                
                QQC2.TextField {
                    id: userField
                    text: n4dAgent.userName
                }
            }
            
            Row {
                id:rowPassword
                spacing: units.smallSpacing
                anchors.right: rowAddress.right
                
                QQC2.Label {
                    anchors.verticalCenter: passwordField.verticalCenter
                    text:i18nd("n4d-qt-agent","Password")
                }
                
                QQC2.TextField {
                    id: passwordField
                    echoMode: TextInput.Password
                    
                    onAccepted: {
                        btnLogin.clicked();
                    }
                }
            }
            
            Row {
                id: rowMessage
                height:32
                width: parent.width
                anchors.horizontalCenter:parent.horizontalCenter
                
                Kirigami.InlineMessage {
                    id: errorLabel
                    //anchors.fill:parent
                    type: Kirigami.MessageType.Error
                    width:parent.width
                    
                }
            }
            
            Row {
                id: rowButtons
                topPadding: units.largeSpacing
                anchors.right: parent.right
                spacing: units.smallSpacing
                
                QQC2.Button {
                    id: btnCancel
                    text:i18nd("n4d-qt-agent","Cancel")
                    
                    onClicked: {
                        root.canceled();
                        
                    }
                }
                
                QQC2.Button {
                    id: btnLogin
                    text:i18nd("n4d-qt-agent","Login")
                    
                    onClicked: {
                        n4dAgent.requestTicket(addressField.text,userField.text,passwordField.text);
                        passwordField.text="";
                        firstPage.enabled=false;
                        errorLabel.visible=false;
                    }
                }
                
            }
        }
    }
    
    QQC2.Pane {
        id: secondPage
        width: 400
        height: 240
        visible: false
        
        Column {
            anchors.fill:parent
            spacing: units.largeSpacing
            
            QQC2.Label {
                topPadding: units.largeSpacing
                anchors.horizontalCenter:parent.horizontalCenter
                text: i18nd("n4d-qt-agent","Logged as:")
            }
            QQC2.Label {
                
                anchors.horizontalCenter:parent.horizontalCenter
                text: userField.text
            }
            
            QQC2.Button {
                topPadding: units.largeSpacing
                anchors.horizontalCenter:parent.horizontalCenter
                
                text: i18nd("n4d-qt-agent","Back")
                
                onClicked: {
                    root.pop();
                }
            }
        }
    }
}
