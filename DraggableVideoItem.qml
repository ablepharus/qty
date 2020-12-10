import QtQuick 2.0

MouseArea {
    property int itemHeight: 120
    property int itemMargin: 12
    id: mouseArea

    height: itemHeight

    function strFillWidth(s, width, fillChar) {
        return (new Array( (width + 1) - ("%1".arg(s).length))).join(fillChar) + "%1".arg(s);
    }
    function secondsToTimeStr(s) {
        return "%1:%2".arg(Math.floor(s/60)).arg(strFillWidth(Math.round(s%60), 2, '0'))
    }
    //drag.axis: Drag.YAxis
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
            //drag.source.parent = parent;
        }
        onDropped: {
            drag.source.parent = mouseArea.parent
        }
    }

    VideoItem {
        anchors.fill: parent
        id: li

        states: [
            State {
                when: li.Drag.active
                ParentChange { target: li; parent: mouseArea.parent }
                //AnchorChanges {
                //    target: li
                    //anchors.horizontalCenter: undefined
                   //anchors.verticalCenter: undefined
                //   }
            }
        ]

        Drag.active: mouseArea.drag.active
        Drag.hotSpot.x: itemHeight / 2
        Drag.hotSpot.y: 34
        Drag.onDragStarted: console.log("Dragging")
    }
}





/*##^## Designer {
    D{i:0;autoSize:true;height:200;width:640}
}
 ##^##*/
