import QtQuick 2.9
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.2
Rectangle {
    anchors.fill: parent
    ColumnLayout {
        anchors.fill: parent
        SearchBar
        {
            id: searchBar
            Layout.fillHeight: false
            Layout.fillWidth: true

        }
        VideoList {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
