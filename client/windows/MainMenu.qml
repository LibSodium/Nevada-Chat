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
    }
}
