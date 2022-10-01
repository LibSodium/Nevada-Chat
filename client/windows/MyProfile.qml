import QtQuick
import Backend

Item
{
    id: root
    width: 500
    height: 500
    property string name: "Example Name"
    property string bio: "Example bio"
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
        Rectangle//ImageProvider
        {
            radius: 30
            width: 250
            height: width
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 25
            anchors.leftMargin: 25
            //source: ":/images/resources/images/user_default.png"
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/
