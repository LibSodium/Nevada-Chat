import QtQuick
import QtQuick.Controls
import Backend

Item
{
    id: root
    property string chat_key
    property string chat_name: "Example Name Example Name"
    property string last_seen: "last seen 32 minutes ago"

    function loadHistory(chat_key)
    {

    }

    function sendMessage(mess)
    {
        if(mess === "") return
        list_model.append({m_text: mess, m_mine: true})
    }

    function displayMessage(key, time, mess, mine)
    {

    }

    function setChat(key, name, chat_photo)
    {
        chat_key = key
        chat_name = name
        photo.image = chat_photo
    }

    Item
    {
        id: top_bar
        height: 60
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        Rectangle
        {
            anchors.fill: parent
            color: "#292C39"
        }
        ImageProvider
        {
            id: photo
            source: ":/images/resources/images/user_default.png"
            radius: 360
            height: 50
            width: height
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
        }
        Text
        {
            id: last_seen
            text: root.last_seen
            anchors.left: photo.right
            anchors.leftMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            color: "#b9b9b9"
            font.pixelSize: 15
        }
        Text
        {
            id: name
            text: root.chat_name
            anchors.left: photo.right
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 3
            color: "white"
            font.pixelSize: 18
        }
    }

    ListView
    {
        id: list_view
        anchors.top: top_bar.bottom
        anchors.bottom: bottom_bar.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 5
        anchors.bottomMargin: 5
        bottomMargin: 10
        topMargin: 20
        model: list_model
        spacing: 30
        clip: true
        boundsBehavior: Flickable.StopAtBounds
        delegate: Message_Delegate
        {
            width: root.width
            mine: m_mine
            message_text: m_text
        }
        ListModel {id: list_model}
    }

    Item
    {
        id: bottom_bar
        height: 45
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        Rectangle
        {
            anchors.fill: parent
            color: "#292C39"
        }
        TextField
        {
            id: message_text
            placeholderText: "Write message..."
            placeholderTextColor: "#b9b9b9"
            color: "white"
            font.pixelSize: 15
            background: Rectangle {anchors.fill: parent; visible: false}
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.right: send_message.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            verticalAlignment: TextInput.AlignVCenter
            onAccepted:
            {
                sendMessage(message_text.text)
                message_text.clear()
            }
        }
        Item
        {
            id: send_message
            width: 50
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            Rectangle
            {
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                height: 20
                width: 45
                radius: 5
                color: "grey"
                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: parent.color = "#97D2FB"
                    onExited: parent.color = "grey"
                    onClicked:
                    {
                        sendMessage(message_text.text)
                        message_text.clear()
                    }
                }
            }
        }
    }
}
