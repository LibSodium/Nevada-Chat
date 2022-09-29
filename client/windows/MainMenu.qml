import QtQuick

Item
{
    id: root
    anchors.fill: parent
    Rectangle
    {
        anchors.fill: parent
        color: "#313645"
    }

    ChatList {id: chat_list}

    Messanger
    {
        id: messanger
        anchors.left: chat_list.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        visible: false
    }
    Text
    {
        id: select_chat
        anchors.left: chat_list.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        text: "Choose a chat to start messaging..."
        color: "white"
        font.pixelSize: 20
        visible: !messanger.visible
    }
}
