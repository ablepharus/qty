import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.11
import org.kde.kirigami 2.4 as Kirigami

Rectangle {

    color: "green"

	ListView {
	    anchors.fill: parent
	    model: ListModel {
		ListElement {
		    title: "Everything "
		    thumbnail: "https://i.ytimg.com/vi/deMGCdOZS-Y/maxresdefault.jpg"
		    duration: 1214
		    uploader: "CinemaSins"
		    view_count: 402018
		    upload_date: 20190608
		}
		ListElement {
		    title: "Even more stuffy"
		    thumbnail: "https://i.ytimg.com/vi/deMGCdOZS-Y/maxresdefault.jpg"
		    duration: 1214
		    uploader: "CinemaSins"
		    view_count: 402018
		    upload_date: 20190608
		}
	    }

    delegate: RowLayout {
        //anchors.fill:parent;
        Label { text: title }
        Label {
            Layout.fillWidth: true
            text: uploader;
            horizontalAlignment: "AlignRight";
            color: "white" } }
    }
}


//}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
