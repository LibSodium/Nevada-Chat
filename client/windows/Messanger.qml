import QtQuick
import Backend

Item
{
    id: root
    property string chat_key
    property alias  photo: photo
    property string last_seen
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
    }
    Item
    {
        id: bottom_bar
        height: 60
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        Rectangle
        {
            anchors.fill: parent
            color: "#292C39"
        }
    }
}
