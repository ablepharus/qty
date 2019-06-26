import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4

import VLCQt 1.1

ApplicationWindow {
    visible: true
    id: window
    width: 1000
    height: 1000
    title: qsTr("qYT")

    SplitView {
        anchors.fill: parent
        orientation: Qt.Horizontal
        SearchPage{
            id: searchPage
            Layout.fillWidth: false
            Layout.fillHeight: true
        }
        Rectangle{
            VlcVideoOutput{
                id: videoOut
                anchors.fill: parent
                source: videoPlayer.player

                MouseArea{
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton | Qt.MiddleButton
                    onClicked: {
                        console.log("Clicking stuff", mouse)
                        if(mouse.button == Qt.RightButton)
                        {
                            console.log("player state: ", videoPlayer.player.state)
                            videoPlayer.player.state == 3 ? videoPlayer.player.pause() : videoPlayer.player.play()
                        }
                    }
                    onDoubleClicked: {
                        console.log("Double click, going fullscreen")
                        if (window.visibility == 5) {
                            window.showNormal()
                        }
                        else {
                            window.showFullScreen()
                            searchPage.Layout.minimumWidth = 0
                        }
                    }
                }
            }
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 223
            Layout.minimumHeight: 161
            color: "black"
        }
    }
}
