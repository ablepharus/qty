import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.11
import org.kde.kirigami 2.4 as Kirigami


Rectangle {

    RowLayout {
        property int visualIndex: index

        //height: itemHeight + 2 * itemMargin
        clip: true

        x: itemMargin; y: itemMargin
        //height: itemHeight
        height: parent.height - itemMargin * 2
        width: parent.width - itemMargin * 2

        //anchors.top: parent.top

        // image and time
        Rectangle {
            width: itemHeight * 1.5; height: itemHeight
            color: "darkgray"
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

                FontMetrics { id: metrics }
                Label {
                    text: title
                    id: titleLabel

                    topPadding: font.pixelSize - contentHeight + 1
                    wrapMode: Text.NoWrap
                    style: "Raised"
                    verticalAlignment: Text.AlignTop
                    topInset: 0
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
                        //text: "on %1".arg(upload_date)
                        text: upload_date
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
                    bottomPadding: -4
                    leftPadding: 0
                    //transformOrigin: Item.Center
                    //anchors.bottom: parent.bottom
                    //anchors.bottomMargin: 0
                }
            }
        }


    }
}
