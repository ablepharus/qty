import QtQuick 2.9
import QtQuick.Layouts 1.3

Rectangle {
    ColumnLayout {
        SearchBar
        {
            id: searchBar
            width: window.width
            Layout.fillHeight: false

        }
        VideoList {
            Layout.fillHeight: true
            width: window.width
        }

    }
}
