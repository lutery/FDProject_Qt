import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import one.chchy.FDObject 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("检测占用，解除占用")

    FDObject{
        id: fdObject
    }

    ListModel{
        id: fileModel
        ListElement{
            fileUrl: "C:\\text.txt"
        }
    }

    ListModel{
        id: progressModel
    }

    Component{
        id: idFileUrl
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
    }

    ColumnLayout{
        id: mainLayout
        anchors.fill: parent
        spacing: 4

        Label{
            text: qsTr("文件")

            Layout.alignment: Qt.AlignTop
            Layout.topMargin: 20
            Layout.leftMargin: 30
        }

        Rectangle{
            Layout.leftMargin: 30
            Layout.rightMargin: 30
            Layout.topMargin: 10
            Layout.preferredHeight: 100
            Layout.fillWidth: true
            Layout.fillHeight: true

            ListView{
                id: listFiles

                anchors.margins: 2
                anchors.fill: parent
                model: fileModel
//                delegate: Rectangle {
//                    height: 25
////                    width: 100
//                    Text { text: fileUrl }
//                }

                delegate: idFileUrl

                highlight: Rectangle{
                    color: "lightblue"
                }
            }

            border.color: "black"

            DropArea{
                anchors.fill: parent
                onDropped: {
                    if (drop.hasUrls){
                        for (var i = 0; i < drop.urls.length; ++i){
                            listFiles.model.append({
                                                       "fileUrl" : drop.urls[i]
                                                   });
                        }
                    }
                }
            }

//            color: "blue"
        }

        Label{
            text: qsTr("占用的程序")

            Layout.topMargin: 20
            Layout.leftMargin: 30
        }

        Rectangle{
            Layout.leftMargin: 30
            Layout.rightMargin: 30
            Layout.topMargin: 10
            Layout.preferredHeight: 100
            Layout.fillWidth: true
            Layout.fillHeight: true

            border.color: "black"

            ListView{
                id: listOccupy

                anchors.margins: 2
                anchors.fill: parent
                model: progressModel
                delegate: Rectangle {
                    height: 25
//                    width: 100
                    Text { text: progressInfo }
                }
            }

//            color: "red"
        }

        RowLayout{

            Layout.bottomMargin: 5
            Layout.leftMargin: 30
            Layout.rightMargin: 30

            Rectangle{
                Layout.fillWidth: true
            }

            Button{
                text: "查询"
                onClicked: {
                    if (listFiles.currentIndex >= 0){
                        var fileUrl = fileModel.get(listFiles.currentIndex).fileUrl
                        console.log(fileUrl)
                        fdObject.analysis(fileUrl)
                    }
                }
            }

            Button{
                text: "解锁"
                onClicked: {
                    listFiles.currentIndex = 0
                }
            }

            Button{
                text: "取消"
            }
        }

//        Rectangle{
//            width: 100
//            Layout.fillHeight: true
//            Layout.fillWidth: true
////            color: "red"
//        }
    }

//    SwipeView {
//        id: swipeView
//        anchors.fill: parent
//        currentIndex: tabBar.currentIndex

//        Page1 {
//        }

//        Page {
//            Label {
//                text: qsTr("Second page")
//                anchors.centerIn: parent
//            }
//        }
//    }

//    footer: TabBar {
//        id: tabBar
//        currentIndex: swipeView.currentIndex
//        TabButton {
//            text: qsTr("First")
//        }
//        TabButton {
//            text: qsTr("Second")
//        }
//    }
}
