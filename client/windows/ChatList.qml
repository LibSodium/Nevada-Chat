import QtQuick
import QtQuick.Controls

Item
{
    id: root
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    width: 300
    Rectangle
    {
        id: background
        anchors.fill: parent
        color: "#3D4357"
    }
    Item
    {
        id: search
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: 50
        Rectangle
        {
            anchors.fill: parent
            anchors.margins: 10
            radius: 5
            color: "#292C39"
            TextField
            {
                id: search_text
                placeholderText: "Search..."
                placeholderTextColor: "#b9b9b9"
                color: "white"
                font.pixelSize: 15
                background: Rectangle {anchors.fill: parent; visible: false}
                anchors.fill: parent
                verticalAlignment: TextInput.AlignVCenter
                onAccepted:
                {
                    search_text.clear()
                }
            }
        }
    }

    Component.onCompleted:
    {
        
    }

    ListView
    {
        id: list_view
        anchors.top: search.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottomMargin: 5
        boundsBehavior: Flickable.StopAtBounds
        model: list_model
        delegate: ChatList_Delegate
        {
            width: root.width
            chat_name: m_name
            chat_key: m_key
            last_message: m_message
            last_mess_time: m_time
            unreaded_messages: m_unreaded
        }
        ListModel {id: list_model}
    }
}
