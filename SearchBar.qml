import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    property string search_text: searchText.text
    signal searchClick()
    onSearchClick: {
        searchText.focus = true
        videosModel.query(search_text)
    }
    height: searchText.height + 20

    RowLayout
    {
        id: rowLayout
        // anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.leftMargin: 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 10
       ///  width: parent.width


        spacing: 0

        TextField
        {
            focus: true
            Layout.fillWidth: true
            id: searchText
            width: parent.width
            onAccepted: searchClick()
            text: "everything wrong with"
            //onEditingFinished: searchClick()
        }
        Button
        {
            Layout.fillWidth: false

            text: 'Search'
            MouseArea
            {
                anchors.fill: parent
                onClicked: searchClick()
            }
        }
    }
}
