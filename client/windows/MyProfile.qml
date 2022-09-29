import QtQuick
import Backend

Item
{
    id: root
    Rectangle
    {
        id: blackout
        anchors.fill: parent
        color: "black"
        opacity: 0.7
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                root.visible = false
            }
        }
    }

    Rectangle
    {
        id: background
        anchors.centerIn: parent
        width: 700
        height: 500
        radius: 40
        color: "#3D4357"
        ImageProvider
        {
            radius: 30
            width: 250
            height: width
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 25
            anchors.leftMargin: 25
            source: ":/images/resources/images/user_default.png"
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.66;height:480;width:640}
}
##^##*/
