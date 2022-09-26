import QtQuick
import QtQuick.Window

Window
{
    id: core
    x: 0
    y: 0
    width: 900
    height: 500
    minimumHeight: 350
    minimumWidth: 350
    visibility: "Maximized"
    color: "black"
    visible: true

    function logIn()
    {

    }

    function logOut()
    {

    }


    StartPage
    {
        id: start_page
        visible: true
        anchors.centerIn: parent
    }

    MainMenu
    {
        id: main_menu
        visible: false
    }

    MyProfile
    {
        id: my_profile
        anchors.fill: parent
        visible: false
    }
}
