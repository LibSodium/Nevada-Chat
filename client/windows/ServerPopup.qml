import QtQuick 

Item 
{
    id: root
    anchors.fill: parent
    property string text
    property bool closeable: true
    Rectangle
    {
        anchors.fill: parent
        color: "black"
        opacity: 0.8
        MouseArea
        {
            anchors.fill: parent
            onClicked: 
            {
                if(!closeable) return
                root.visible = false
            }
        }
    }

    Rectangle
    {
        id: background
        anchors.centerIn: parent
        radius: 20
        width: 400
        height: 150
        color: "#313645"
        Text
        {
            anchors.centerIn: parent
            text: root.text
            color: "white"
            font.pixelSize: 30
        }
    }
}
