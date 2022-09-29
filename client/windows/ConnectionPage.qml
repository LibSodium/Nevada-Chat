import QtQuick 
import QtQuick.Controls
Item 
{
    id: root
    width: 500
    height: connect ? 380 : 280
    Behavior on height {NumberAnimation{duration: 200}}
    property bool connect: true
    
    Rectangle
    {
        id: background
        anchors.fill: parent
        radius: 30
        color: "#313645"
        Text
        {
            anchors.top: parent.top
            text: "Connect"
            color: connect ? "white" : "grey"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 20
            font.pixelSize: 40
            anchors.horizontalCenterOffset: -80
            MouseArea
            {
                visible: !connect
                anchors.fill: parent
                onClicked:
                {
                    focus = true
                    connect = true
                }
            }
        }
        Text
        {
            anchors.top: parent.top
            text: "Create"
            color: !connect ? "white" : "grey"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 20
            font.pixelSize: 40
            anchors.horizontalCenterOffset: 80
            MouseArea
            {
                visible: connect
                anchors.fill: parent
                onClicked:
                {
                    focus = true
                    connect = false
                }
            }
        }
        
        CustomTextInput
        {
            id: server_ip
            height: 45
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 130
            anchors.rightMargin: 40
            anchors.leftMargin: 40
            placeholder_text: "Server IP..."
            only_numbers: true
            text_area.text: "95.31.196.133"
            text_area.onAccepted: 
            {
                server_port.text_area.focus = true
            }

            onTextChanged: 
            {
                if(server_ip.text != "" && server_port.text != "")
                {
                    connect_button.clickable = true
                    connect_button.hover = true
                }
                else
                {
                   connect_button.clickable = false
                   connect_button.hover = false 
                }
            }
        }
        
        CustomTextInput
        {
            id: server_port
            height: 45
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: connect ? 210 : 130
            Behavior on anchors.topMargin {NumberAnimation{duration: 200}}
            anchors.rightMargin: 40
            anchors.leftMargin: 40
            text_area.text: "2222"
            placeholder_text: "Server port..."
            only_numbers: true
            onTextChanged: 
            {
                if(connect && server_ip.text != "" && server_port.text != "")
                {
                    connect_button.clickable = true
                    connect_button.hover = true
                }
                else if(!connect && server_port.text != "")
                {
                    connect_button.clickable = true
                    connect_button.hover = true
                }
                else
                {
                    connect_button.clickable = false
                    connect_button.hover = false 
                }
            }
        }
        
        
        
        CustomButton
        {
            id: connect_button
            height: 40
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
            width: 160
            text: connect ? "Connect" : "Create"
            mouse_area.onClicked:
            {
                focus = true
                if(connect)
                {
                    if(cl.connect(server_ip.text, server_port.text))
                    {
                        root.visible = false
                        start_page.visible = true
                    }
                    else
                    {
                        connect_error.visible = true
                    }
                }
                else
                {
                    if(server_run)
                    {
                        already_running.visible = true
                        return
                    }

                    if(sv.start(server_port.text))
                    {
                        server_run = true
                        connect = true
                    }
                    else
                    {
                        
                    }
                }
            }
        }
    }
    ServerPopup
    {
        id: connect_error
        visible: false
        text: "Server is unavailable."
    }
    ServerPopup
    {
        id: already_running
        visible: false
        text: "Server is already running."
    }
}
