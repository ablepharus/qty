import QtQuick 2.9
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.2
import QtQuick.Controls 2.5

Rectangle {
    clip: true
    ColumnLayout {
        anchors.fill: parent

        SearchBar
        {
            clip: true
            id: searchBar
            Layout.fillHeight: false
            Layout.fillWidth: true
        }
        SearchResultList
        {
            id: resultList
        }


    }
}







/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
