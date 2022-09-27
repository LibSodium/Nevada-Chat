import QtQuick 

Item 
{
    id: root
    property alias mouse_area: mouse_area
    
    property string active_color: "#6F6F6F"
    property string inactive_color: "#575757"
    
    property string selected_color: "#6494B6"
    property string border_color: "#00ffffff"
    property string text: "Button"
    property bool hover: false
    property bool clickable: false
    Rectangle
    {
        anchors.fill: parent
        id: background
        radius: 5
        color: clickable ? active_color : inactive_color
        border.width: 2
        border.color: border_color
        Text
        {
            anchors.centerIn: parent
            text: root.text
            color: clickable ? "white" : "#b9b9b9"
            font.pixelSize: 20
        }
        MouseArea
        {
            id: mouse_area
            visible: clickable
            hoverEnabled: hover
            anchors.fill: parent
            onEntered: 
            {
                background.color = selected_color
            }
            onExited: 
            {
                background.color = active_color
            }
        }
    }
}
