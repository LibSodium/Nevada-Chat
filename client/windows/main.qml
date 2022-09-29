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
    minimumWidth: 700
    visibility: "Maximized"
    color: "black"
    visible: true
    
    property bool server_run: false
    property string my_key: "0"
    property var current_online: []
    
    function logIn()
    {

    }

    function logOut()
    {

    }
    
    Timer
    {
        id: update_online
        interval: 1000
        running: true
        onTriggered: 
        {
            cl.getOnlineList()
            restart()
        }
    }

    Connections
    {
        target: cl
        function onConnectionLost()
        {
            connection_lost.visible = true
        }
        function onConnectionRestored()
        {
            connection_lost.visible = false
        }
        function onAcquireOnlineList(list)
        {
            current_online = list
        }
    }
    
    ConnectionPage
    {
        id: connection_page
        visible: true
        anchors.centerIn: parent
    }
    
    StartPage
    {
        id: start_page
        visible: false
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
    
    ServerPopup
    {
        id: connection_lost
        text: "Connection to server lost..."
        visible: false
        closeable: false
    }
}
