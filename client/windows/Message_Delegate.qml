import QtQuick

Item
{
    id: root
    height: txt.implicitHeight
    property bool mine
    property string message_text: "example text"
    property string owner_name
    property string time: "00:00"

    Component.onCompleted:
    {
        if(mine)
        {
            photo.anchors.right = root.right
            photo.anchors.rightMargin = 5
            message_background.anchors.right = photo.left
            message_background.anchors.rightMargin = 5
            txt.horizontalAlignment = Text.AlignRight
            txt.anchors.right = message_background.right
            message_time.anchors.right = message_background.right
        }
        else
        {
            photo.anchors.left = root.left
            photo.anchors.leftMargin = 5
            message_background.anchors.left = photo.right
            message_background.anchors.leftMargin = 5
            txt.horizontalAlignment = Text.AlignLeft
            txt.anchors.left = message_background.left
            message_time.anchors.left = message_background.left
        }
    }

    Rectangle
    {
        id: photo
        radius: 360
        width: 30
        height: width
    }
    Text
    {
        id: message_time
        text: time
        color: "white"
        anchors.bottom: message_background.top
        anchors.leftMargin: 7
        anchors.rightMargin: 7
        font.pixelSize: 14
    }

    Rectangle
    {
        id: message_background
        width: txt.width + 10
        height: txt.implicitHeight + 5
        color: mine ? "#2B5271" : "#264953"
        radius: 10
        Text
        {
            id: txt
            text: message_text
            font.pixelSize: 15
            anchors.top: parent.top
            width: txt.implicitWidth > (root.width / 2) ? (root.width / 2) : txt.implicitWidth + 10
            color: "white"
            wrapMode: Text.WordWrap
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            topPadding: 5
            bottomPadding: 5
            onWidthChanged:
            {

            }
        }
    }
}


