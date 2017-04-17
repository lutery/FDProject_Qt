import QtQuick 2.0
import QtQuick.Layouts 1.3

Item {
    id: fileurldelegate
    width: parent.width
    height: 30

    MouseArea{
        anchors.fill: parent
        onClicked: fileurldelegate.ListView.view.currentIndex = index
    }

    RowLayout{
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        spacing: 8
        Text{
            id: id_fileurl
            text: fileUrl
            color: fileurldelegate.ListView.isCurrentItem ? "red" : "black"
            font.pixelSize: fileurldelegate.ListView.isCurrentItem ? 22 : 18
            Layout.fillWidth: true
        }
    }
}
