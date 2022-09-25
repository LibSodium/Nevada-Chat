import QtQuick
import QtQuick.Controls

Item
{
    id: root
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    width: 300
    Rectangle
    {
        id: background
        anchors.fill: parent
        color: "#3D4357"
    }
    Item
    {
        id: search
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: 50
        Rectangle
        {
            anchors.fill: parent
            anchors.margins: 10
            radius: 5
            color: "#292C39"
            TextInput
            {
                font.pixelSize: 17
                text: "Search..."
                color: "#b9b9b9"
                anchors.fill: parent
                clip: true
                verticalAlignment: TextInput.AlignVCenter
                anchors.leftMargin: 30
                onAccepted:
                {
                    focus = false
                }
            }
        }
    }

    ListView
    {
        id: list_view
        anchors.top: search.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottomMargin: 5
        boundsBehavior: Flickable.StopAtBounds
        model: 5
        delegate: ChatList_Delegate
        {
            width: root.width
        }
        ListModel {id: list_model}
    }
}
