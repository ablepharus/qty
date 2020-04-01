import QtQuick 2.9
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.2
import QtQuick.Controls 2.5

Rectangle {
    Layout.fillHeight: true
    Layout.fillWidth: true

    BusyIndicator{
        running: videosModel.isBusy
        anchors.fill: parent
        background: VideoList {
            footer: Label {
                MouseArea {
                    anchors.fill: parent
                    onClicked: videosModel.query( searchBar.search_text,
                                   videosModel.rowCount() + 10)
                }
                text: "Load more"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            footerPositioning: ListView.OverlayFooter
        }
    }

}
