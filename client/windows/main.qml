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

    StartPage
    {
        id: start_page
        visible: false
    }

    MainMenu
    {
        id: main_menu
    }

    MyProfile
    {
        id: my_profile
        anchors.fill: parent
        visible: false
    }
}
