import QtQuick
import QtQuick.Controls

Item
{
    id: root
    property string placeholder_text
    property string text: text_area.displayText
    property alias text_area: text_area
    property bool only_numbers: false
    property var num_validator: RegularExpressionValidator {regularExpression: /[0-9.]+/}
    
    onOnly_numbersChanged: 
    {
        if(only_numbers)
        {
            text_area.validator = num_validator
        }
        else
        {
            
        }
    }
    
    TextField
    {
        id: text_area
        anchors.fill: parent
        height: 45
        placeholderTextColor: "#b9b9b9"
        leftPadding: 15
        rightPadding: 15
        horizontalAlignment: "AlignHCenter"
        clip: true
        font.pointSize: 21
        placeholderText: placeholder_text
        anchors.verticalCenterOffset: -100
        color: "white"
        background: Rectangle
        {
            radius: 5
            color: "#292C39"
            border.color: "white"
            border.width: 1
        }
    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
