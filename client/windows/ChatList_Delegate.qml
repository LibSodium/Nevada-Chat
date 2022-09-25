import QtQuick

Item
{
    id: root
    height: 65
    property string chat_name: "Example Name Example Name"
    property string last_seen: "12:03"
    property string last_message: "Example last message that can be very long and need to cut it"
    property string chat_key: "7gHytj5goU4"
    property string last_mess_time: "22:34"
    property string unreaded_messages: "+1"
    property bool is_online: true

    Rectangle
    {
        id: background
        color: "#3D4357"
        anchors.fill: parent
        Rectangle
        {
            id: photo
            radius: 360
            width: 50
            height: width
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 10
        }
        Item
        {
            id: last_online
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.rightMargin: 0
            height: 30
            width: 60
            Text
            {
                color: "blue"
                anchors.fill: parent
                text: is_online ? "online" : null
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 16
            }
        }

        Item
        {
            id: unreaded
            height: 30
            width: 40
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.rightMargin: 5
            anchors.bottomMargin: 5
            Rectangle
            {
                anchors.centerIn: parent
                width: unreaded_count.implicitWidth + 10
                height: 20
                color: "black"
                radius: 360
                Text
                {
                    id: unreaded_count
                    anchors.centerIn: parent
                    text: unreaded_messages
                    color: "white"
                    font.pixelSize: 17
                    font.bold: true
                }
            }
        }

        Text
        {
            id: name
            text: chat_name
            color: "white"
            font.pixelSize: 17
            anchors.top: parent.top
            anchors.left: photo.right
            anchors.right: last_online.left
            height: 30
            anchors.leftMargin: 10
            anchors.topMargin: 8
            elide: Text.ElideRight
        }

        Text
        {
            id: last
            text: last_message
            color: "white"
            font.pixelSize: 15
            anchors.bottom: parent.bottom
            anchors.left: photo.right
            anchors.right: unreaded.left
            height: 30
            anchors.leftMargin: 10
            elide: Text.ElideRight
        }
    }
}
