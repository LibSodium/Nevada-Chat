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
    ListView
    {
        id: list_view
        anchors.fill: parent
        model: 5
        boundsBehavior: Flickable.StopAtBounds
        delegate: ChatList_Delegate
        {
            width: root.width
        }
        ListModel {id: list_model}
    }
}
