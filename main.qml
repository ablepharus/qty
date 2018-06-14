import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    id: window
    width: 640
    height: 480
    title: qsTr("Hello World")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        SearchPage{

        }
        VideoList {
        }
        SearchBar
        {
        }


    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("SearchPage")
        }
        TabButton {
            text: qsTr("VideoList")
        }
        TabButton {
            text: qsTr("SearchBar")
        }
    }
}
