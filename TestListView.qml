import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.11
import org.kde.kirigami 2.4 as Kirigami


ListView {
    id: videoListView
    // TODO model:
    clip: true
    snapMode: ListView.SnapToItem

    highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
    delegate: DraggableVideoItem {
        property ListView myView: videoListView
        onClicked:  {
                       //videoPlayer.play(itemAt(index, 0)["formats"])
                       //videoPlayer.play(formats)
                       console.log("adding entry")
                       //console.log(model.json)
                       //console.log(index)
                       //console.log(currentItem) // QMLMouseArea
                       videoPlayer.playlist.copyEntry(videosModel, index)
                       //videoPlayer.playlist.copyMyEntry(index)
                       console.log(videosModel)
                       //videoPlayer.playlist.addEntry(json)
                   }

        hoverEnabled: true
        onHoveredChanged: {
            myView.currentIndex = index
        }
    }

    keyNavigationWraps: true
}




















/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
