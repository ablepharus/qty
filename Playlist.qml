import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    id: playlistControl
    Button {
        text: "Swish"
        onClicked: videoPlayer.playlist.model.move(0, 2)
        z: 3
    }

    ListView {
        anchors.fill: parent
        id: playlistView
        model: videoPlayer.playlist.model
        //highlightFollowsCurrentItem: false
        currentIndex: videoPlayer.playlist.currentTrackIndex
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }

        delegate: VideoItem {
            property ListView myView: playlistView
            onClicked: videoPlayer.playlist.playAt(index)

        }
    }
}
