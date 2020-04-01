import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.11
import org.kde.kirigami 2.4 as Kirigami


MouseArea {
    property int itemHeight: 120
    property int itemMargin: 12
    id: mouseArea
    // width: 520
    height: itemHeight + 2 * itemMargin
    clip: true

    function strFillWidth(s, width, fillChar) {
        return (new Array( (width + 1) - ("%1".arg(s).length))).join(fillChar) + "%1".arg(s);
    }
    function secondsToTimeStr(s) {
        return "%1:%2".arg(Math.floor(s/60)).arg(strFillWidth(Math.round(s%60), 2, '0'))
    }
    drag.axis: Drag.YAxis
    //drag.target: parent
    drag.target: li
    //hoverEnabled: true
    //onHoveredChanged: {
    //    myView.currentIndex = index
    //}
    DropArea {
        anchors.fill: parent
        onEntered: {
            console.log(drag.source);
            console.log("from " + drag.source.visualIndex + " to " + index);
            if( drag.source.visualIndex !== index)
                myView.model.move(drag.source.visualIndex, index);
        }
        onDropped: {
            drag.source.parent = mouseArea.parent
        }
    }

    RowLayout {
        property int visualIndex: index
        clip: true
        x: itemMargin; y: itemMargin
        height: itemHeight
        width: parent.width - itemMargin * 2

        id: li
        //anchors.top: parent.top
        states: [
            State {
                when: li.Drag.active
                ParentChange { target: li; parent: mouseArea.parent }

            },
            State {
                //when: li.Drag.dropped
            }

        ]

        Drag.active: mouseArea.drag.active
        Drag.hotSpot.x: itemHeight / 2
        Drag.hotSpot.y: 34
        Drag.onDragStarted: console.log("Dragging")

        // image and time
        Rectangle {
            width: itemHeight * 1.5; height: itemHeight
            Image {
                // source: "file:///usr/share/icons/breeze/places/symbolic/folder-videos-symbolic.svg"
                fillMode: Image.PreserveAspectCrop
                source:  thumbnail
                anchors.fill: parent
            }
            // place time label on the lower right corner of the image
            Label {
                z: 1
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                color: "white"
                text: secondsToTimeStr(duration)
                background: Rectangle { color: "black" ; opacity: 0.85 }
                padding: 3
            }
        }
        Item{
            height: itemHeight
            Layout.fillWidth: true

            // head {title, uploader, date)
            // text  (has to be shrinkable)
            // foot {view_count,}
            ColumnLayout {
                id: column
                anchors.fill: parent

                Kirigami.Heading {
                    // top has to lie on a line with img top
                    id: titleHeading
                    text: title;
                    level: 2;
                    style: "Raised"
                }
                RowLayout {
                    id: lowerHeading
                    //anchors.left: parent.left; anchors.right: parent.right
                    Label {
                        id: uploaderLabel
                        text: "by %1".arg(uploader)
                        //anchors.left: parent.left
                    }
                    // Item { Layout.fillWidth: true } // spacer, push upload date to the right
                    Label {
                        text: "on %1".arg(upload_date)
                        //background: Rectangle { color: "black" }
                        horizontalAlignment: "AlignRight"
                        Layout.fillWidth: true
                    }
                }
                Label {
                    id: descLabel
                    //anchors.bottom: infoFooter.top
                    text: description
                    wrapMode: Text.WordWrap
                    Layout.fillHeight: true
                    clip: true
                }

                Label {
                    text: "%1 views".arg(view_count)
                    //transformOrigin: Item.Center
                    //anchors.bottom: parent.bottom
                    //anchors.bottomMargin: 0
                }
            }
        }
    }
}
