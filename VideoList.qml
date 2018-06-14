import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0
ScrollView {
ListView {
    id: videoListView
    model: videosModel
    // highlightRangeMode:  ListView.StrictlyEnforceRange
    highlightFollowsCurrentItem: true
    keyNavigationWraps: true

    highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
    delegate: RowLayout {
        width: parent.width
        //Layout.alignment: Qt.AlignLeft
        Rectangle {
            width: 246; height: 138
            Image {
                // source: "file:///usr/share/icons/breeze/places/symbolic/folder-videos-symbolic.svg"

                fillMode: Image.PreserveAspectCrop
                source:  image
                width: 246; height: 138
            }
        }
        ColumnLayout {
            Layout.fillWidth: true
            Label {
                // anchors.top: parent.top;
                // Layout.alignment: Qt.AlignTop
                text: name ;
                style: "Raised"
                anchors.left: parent.left
            }
            Label {
                //anchors.bottom: parent.bottom;
                // Layout.alignment: Qt.AlignBottom
                text: duration
            }
            Label {
                text: author
            }
            Label {
                text: views
            }
            Label {
                text:uploaded
            }
        }
        MouseArea {
            onClicked: console.log(name)
            anchors.fill: parent
            hoverEnabled: true
            onHoveredChanged: {
                videoListView.currentIndex = index
            }
        }
    }
}
}
