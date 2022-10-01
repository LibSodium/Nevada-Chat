import QtQuick

Item
{
    id: root
    width: 500
    height: sign_in ? 380 : 460
    Behavior on height {NumberAnimation{duration: 200}}
    property bool sign_in: true
    
    Connections
    {
        target: cl
        function onSignUpResult(key)
        {
            if(key === "-1")
            {
                login_area.text_area.clear()
                login_area.border_color = "red"
                login_area.text_area.focus = true
            }
            else
            {
                sign_in = true
            }
        }
        function onLogInResult(key, nick)
        {
            if(key === "-1")
            {
                login_area.text_area.clear()
                password_area.text_area.clear()
                login_area.border_color = "red"
                password_area.border_color = "red"
            }
            else if(key === "-2")
            {
                login_area.text_area.clear()
                password_area.text_area.clear()
                already_online.visible = true
            }
            else
            {
                my_key = key
                cl.getChatList(my_key)
                root.visible = false
                main_menu.visible = true
            }
        }
    }
    
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
                    login_area.border_color = "white"
                    password_area.border_color = "white"
                    nickname_area.border_color = "white"
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
                    login_area.border_color = "white"
                    password_area.border_color = "white"
                    nickname_area.border_color = "white"
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
            onTextChanged: 
            {
                if(text != "")
                {
                    border_color = "#00FF22"
                }
                else
                {
                    border_color = "white"
                }
            }
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
            onTextChanged: 
            {
                if(text != "")
                {
                    border_color = "#00FF22"
                }
                else
                {
                    border_color = "white"
                }
            }
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
            onTextChanged: 
            {
                if(text != "")
                {
                    border_color = "#00FF22"
                }
                else
                {
                    border_color = "white"
                }
            }
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
        text: sign_in ? "Sign In" : "Sign Up"
        clickable: true
        hover: true
        mouse_area.onClicked: 
        {
            var login = login_area.text
            var password = password_area.text
            if(!sign_in)
            {
                var nick = nickname_area.text
                cl.trySignUp(login, password, nick)
            }
            else
            {
                cl.tryLogIn(login, password)
            }
        }
    }
    ServerPopup
    {
        id: already_online
        text: "User is already online."
        visible: false
    }
}


