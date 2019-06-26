import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.11

ListView {
    id: videoListView
    model: videosModel

    highlightFollowsCurrentItem: true
    keyNavigationWraps: true
    highlight: Rectangle { color: "lightsteelblue"; radius: 5 }

    delegate:  MouseArea {
        width: parent.width
        height:140
        onClicked: videoPlayer.play(formats)
        hoverEnabled: true
        onHoveredChanged: {
            videoListView.currentIndex = index
        }

        RowLayout {

            Rectangle {
                width: 246; height: 138
                Image {
                    // source: "file:///usr/share/icons/breeze/places/symbolic/folder-videos-symbolic.svg"
                    fillMode: Image.PreserveAspectCrop
                    source:  thumbnail
                    width: 246; height: 138
                }
            }
            Item{
                height: 138
                Layout.fillWidth: true

                ColumnLayout {
                    //height: 246
                    //width: parent.width
                    Layout.fillWidth: true
                    Label {
                        // anchors.top: parent.top;
                        // Layout.alignment: Qt.AlignTop
                        text: title ;
                        style: "Raised"
                        //anchors.left: parent.left

                    }
                    Label {
                        //anchors.bottom: parent.bottom;
                        // Layout.alignment: Qt.AlignBottom
                        text: duration
                    }
                    Label {
                        text: uploader
                    }
                    Label {
                        text: view_count
                    }
                    Label {
                        text: upload_date
                    }
                }
            }


        }
    }
}
/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
