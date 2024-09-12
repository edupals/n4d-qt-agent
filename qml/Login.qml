/*
 * Copyright (C) 2021 Lliurex project
 *
 * Author:
 *  Enrique Medina Gremaldos <quiqueiii@gmail.com>
 *
 * Source:
 *  https://github.com/edupals/n4d-qt-agent
 *
 * This file is a part of n4d-qt-agent
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 */

import Edupals.N4D.Agent 1.0 as N4DAgent

import QtQuick 2.6
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.6 as QQC2
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.kirigami 2.5 as Kirigami

QQC2.StackView {
    id: root
    width: 400
    height: 400
    
    initialItem: firstPage
    
    property alias message: labelCustomMessage.text
    property alias address: addressField.text
    property alias user: userField.text
    property bool showAddress: false
    property alias showCancel: btnCancel.visible
    property bool trustLocal: false
    property var inGroups: []
    
    signal authenticated(var passwd)
    signal logged(var ticket)
    signal canceled()
    signal failed(int code,string what)
    
    N4DAgent.Proxy {
        id: n4dAgent
    }

    function getErrorMessage(code)
    {
        switch (code) {
            case N4DAgent.Status.AuthenticationFailed:
                return i18nd("n4d-qt-agent","Authentication failed");
                
            case N4DAgent.Status.InvalidServerResponse:
                return i18nd("n4d-qt-agent","Invalid server response");
                
            case N4DAgent.Status.UnknownError:
                return i18nd("n4d-qt-agent","Unknown error");
            
            case N4DAgent.Status.InvalidKey:
                return i18nd("n4d-qt-agent","Error reading ticket");
            
            case N4DAgent.Status.InvalidUserGroup:
                return i18nd("n4d-qt-agent","User is not in a valid group");
            
            default:
                return i18nd("n4d-qt-agent","Error:")+code;
        }
    }
    
    Connections {
        target: n4dAgent
        
        function onTicket(code,value) {
            firstPage.enabled=true;
            if (code==N4DAgent.Status.CallSuccessful) {
                if (trustLocal==false) {
                    root.authenticated(passwordField.text);
                }
                passwordField.text="";
                root.push(secondPage);
                root.logged(value);
            }
            else {
                
                if (trustLocal && code==N4DAgent.Status.InvalidUserGroup) {
                    trustLocal=false;
                    userField.text="";
                }
                else {
                    passwordField.text="";
                    errorLabel.text=getErrorMessage(code);
                    errorLabel.visible=true;
                
                    root.failed(code,value);
                }
            }
        }
    }
    
    Component.onCompleted: {
        if (trustLocal) {
            n4dAgent.requestLocalTicket(n4dAgent.userName,root.inGroups);
        }
    }
    
    MouseArea {
        cursorShape: firstPage.enabled==false ? Qt.BusyCursor : Qt.ArrowCursor
        anchors.fill: parent
    }
    
    QQC2.Pane {
        id: firstPage
        width: root.width
        height: root.height
        padding: Kirigami.Units.largeSpacing
        
        ColumnLayout {
            anchors.fill:parent
            spacing: Kirigami.Units.largeSpacing
            
            RowLayout {
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth:true

                Kirigami.Icon {
                    Layout.alignment: Qt.AlignLeft
                    Layout.minimumWidth: Kirigami.Units.iconSizes.large
                    Layout.minimumHeight: width
                    
                    source: "preferences-system-user-sudo"
                }
                
                QQC2.Label {
                    id: labelCustomMessage
                    Layout.alignment: Qt.AlignCenter
                    Layout.fillWidth:true
                    wrapMode:Text.WordWrap
                    
                    text:i18nd("n4d-qt-agent","This action needs authentication against the N4D Server")
                    font.pixelSize:16
                }
            }
            
            QQC2.Label {
                
                id: labelInfoMessage
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth:true
                wrapMode:Text.WordWrap
                
                text:i18nd("n4d-qt-agent","An application is trying to do an action that requires N4D authentication")
                horizontalAlignment:text.AlignCenter
                font.pixelSize:12
            }
                
            GridLayout {
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth:true
                Layout.fillHeight:true
                
                rows:3
                columns:2
                
                QQC2.Label {
                    text:i18nd("n4d-qt-agent","User")
                    Layout.row:0
                    Layout.column:0
                    Layout.alignment: Qt.AlignRight
                }
                
                QQC2.TextField {
                    id: userField
                    text: n4dAgent.userName
                    focus: true
                    
                    Layout.row:0
                    Layout.column:1
                }
                
                QQC2.Label {
                    text:i18nd("n4d-qt-agent","Password")
                    Layout.row:1
                    Layout.column:0
                    Layout.alignment: Qt.AlignRight
                }
                
                QQC2.TextField {
                    id: passwordField
                    echoMode: TextInput.Password
                    Layout.row:1
                    Layout.column:1
                    
                    onAccepted: {
                        btnLogin.clicked();
                    }
                }
                
                QQC2.Label {
                    text:i18nd("n4d-qt-agent","Server")
                    Layout.row:2
                    Layout.column:0
                    Layout.alignment: Qt.AlignRight
                    visible: root.showAddress
                }
                
                QQC2.TextField {
                    id: addressField
                    text: "localhost"
                    Layout.row:2
                    Layout.column:1
                    visible: root.showAddress
                }
                
            }
            
            RowLayout {
                id: rowMessage
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth:true
                
                Kirigami.InlineMessage {
                    id: errorLabel
                    type: Kirigami.MessageType.Error
                    width:parent.width
                    
                }
            }
            
            Item {
                Layout.fillWidth:true
                Layout.fillHeight:true
            }
            
            RowLayout {
                id: rowButtons
                Layout.alignment: Qt.AlignRight | Qt.AlignBottom
                Layout.fillWidth:true
                spacing: Kirigami.Units.smallSpacing
                
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
                        n4dAgent.requestTicket(addressField.text,userField.text,passwordField.text,root.inGroups);
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
        height: 400
        visible: false
        
        ColumnLayout {
            anchors.fill:parent
            spacing: Kirigami.Units.smallSpacing
            
            Item {
                height: 16
            }
            
            QQC2.Label {
                Layout.alignment: Qt.AlignCenter
                
                text: i18nd("n4d-qt-agent","Logged as:")
            }
            
            QQC2.Label {
                Layout.alignment: Qt.AlignCenter
                text: userField.text
            }
            
            QQC2.Button {
                Layout.alignment: Qt.AlignCenter
                width: Kirigami.Units.gridSpacing * 6
                
                text: i18nd("n4d-qt-agent","Back")
                
                onClicked: {
                    trustLocal = false;
                    root.pop();
                }
            }
        }
    }
}
