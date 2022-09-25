import QtQuick

Item
{
    id: root
    height: text.implicitHeight
    property bool mine
    property string message_text: "example text"
    property string owner_name

    Component.onCompleted:
    {
        if(mine)
        {
            photo.anchors.right = root.right
            photo.anchors.rightMargin = 5
            message_background.anchors.right = photo.left
            message_background.anchors.rightMargin = 5
            text.horizontalAlignment = Text.AlignRight
            text.anchors.right = message_background.right
        }
        else
        {
            photo.anchors.left = root.left
            photo.anchors.leftMargin = 5
            message_background.anchors.left = photo.right
            message_background.anchors.leftMargin = 5
            text.horizontalAlignment = Text.AlignLeft
            text.anchors.left = message_background.left
        }
    }

    Rectangle
    {
        id: photo
        radius: 360
        width: 30
        height: width
    }
    Rectangle
    {
        id: message_background
        width: text.width + 15
        height: text.implicitHeight + 5
        color: mine ? "#2B5271" : "#264953"
        radius: 10
        Text
        {
            id: text
            text: message_text
            font.pixelSize: 15
            anchors.top: parent.top
            width: text.implicitWidth > (root.width / 2) ? (root.width / 2) : text.implicitWidth + 10
            color: "white"
            wrapMode: Text.WordWrap
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            topPadding: 5
            bottomPadding: 10
            onWidthChanged:
            {

            }
        }
    }
}
