import QtQuick

Item
{
    id: root
    Rectangle
    {
        id: blackout
        anchors.fill: parent
        color: "black"
        opacity: 0.7
    }

    Rectangle
    {
        id: background
        anchors.centerIn: parent
        width: 700
        height: 500
        radius: 40
        color: "#3D4357"
        Rectangle
        {
            radius: 30
            width: 150
            height: width
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 25
            anchors.leftMargin: 25
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.66;height:480;width:640}
}
##^##*/
