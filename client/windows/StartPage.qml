import QtQuick

Item
{
    id: root
    width: 500
    height: sign_in ? 380 : 470
    Behavior on height {NumberAnimation{duration: 200}}
    property bool sign_in: true
    Rectangle
    {
        id: background
        anchors.fill: parent
        radius: 30
        color: "#313645"

        Text
        {
            anchors.top: parent.top
            text: "Sign In"
            color: sign_in ? "white" : "grey"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 20
            font.pixelSize: 40
            anchors.horizontalCenterOffset: -80
            MouseArea
            {
                visible: !sign_in
                anchors.fill: parent
                onClicked:
                {
                    focus = true
                    sign_in = true
                }
            }
        }
        Text
        {
            anchors.top: parent.top
            text: "Sign Up"
            color: !sign_in ? "white" : "grey"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 20
            font.pixelSize: 40
            anchors.horizontalCenterOffset: 80
            MouseArea
            {
                visible: sign_in
                anchors.fill: parent
                onClicked:
                {
                    focus = true
                    sign_in = false
                }
            }
        }

        CustomTextInput
        {
            id: login_area
            height: 45
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 130
            anchors.rightMargin: 40
            anchors.leftMargin: 40
            placeholder_text: "Login..."
        }

        CustomTextInput
        {
            id: nickname_area
            visible: anchors.topMargin > 210
            height: 45
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: sign_in ? 210 : 290
            Behavior on anchors.topMargin {NumberAnimation{duration: 200}}
            anchors.rightMargin: 40
            anchors.leftMargin: 40
            placeholder_text: "Nickname..."
        }

        CustomTextInput
        {
            id: password_area
            height: 45
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 210
            anchors.rightMargin: 40
            anchors.leftMargin: 40
            placeholder_text: "Password..."
        }
    }
    
    CustomButton
    {
        id: sign_in_button
        height: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        width: 160
        text: "Sign In"
    }
}


