import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.11

ApplicationWindow {
    visible: true
    id: window
    width: 640
    height: 480
    title: qsTr("Hello World")
    SearchPage{
        anchors.fill: parent
    }
}
