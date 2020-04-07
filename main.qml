import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4

import VLCQt 1.1


ApplicationWindow {
    visible: true
    id: window
    width: 1700
    height: 820
    title: qsTr("qYT")

    SplitView {
        Keys.onRightPressed: videoPlayer.seekFwd()
        Keys.onLeftPressed: videoPlayer.seekBck()
        Keys.onUpPressed: videoPlayer.seekFwdFwd()
        Keys.onDownPressed: videoPlayer.seekBckBck()
        Keys.onSpacePressed: videoOut.togglePlay()
        Keys.onPressed: {
            if (event.key === Qt.Key_F)
                videoOut.toggleFullscreen()
            if(event.key === Qt.Key_Q)
                window.close()
            if(event.key === Qt.Key_Greater)
                videoPlayer.next()
            if(event.key === Qt.Key_Less)
                videoPlayer.prev()
        }
        focus: true

        anchors.fill: parent
        orientation: Qt.Horizontal

        SearchPage{
            id: searchPage
            Layout.fillWidth: false
            Layout.fillHeight: true
            Layout.preferredWidth: 600
            Layout.minimumWidth: 600
        }
        Rectangle{
            focus: true
            Keys.onRightPressed: {
                console.log("right, right?")
                videoPlayer.seekFwd()
            }
            Keys.onLeftPressed: {
                console.log("left")
                videoPlayer.seekBck()
            }

            VlcVideoOutput{
                function togglePlay() {
                    console.log("Play or Pause, player state ",
                                videoPlayer.player.state)
                    if(videoPlayer.player.state == 3)
                        videoPlayer.player.pause()
                    else if(videoPlayer.player.state == 6)
                        videoPlayer.playFirst()
                    else
                        videoPlayer.player.play()
                }
                function toggleFullscreen() {
                    if (window.visibility == 5) {
                        window.showNormal()
                    }
                    else {
                        window.showFullScreen()
                        searchPage.Layout.minimumWidth = 0
                    }
                }

                id: videoOut
                anchors.fill: parent
                source: videoPlayer.player

                Keys.onRightPressed: {
                    console.log("right, right?")
                    videoPlayer.seekFwd()
                }
                Keys.onLeftPressed: {
                    console.log("left")
                    videoPlayer.seekBck()
                }
                MouseArea{
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton | Qt.MiddleButton
                    onClicked: {
                        console.log("Clicking stuff", mouse)
                        if(mouse.button == Qt.RightButton)
                            videoOut.togglePlay()
                    }
                    onDoubleClicked: {
                        videoOut.toggleFullscreen()
                        console.log("Double click, going fullscreen")
                    }
                }
            }
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 223
            Layout.minimumHeight: 161
            color: "black"
        }
        Playlist {
            width: 600
        }
    }
}
