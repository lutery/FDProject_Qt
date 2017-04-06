import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("检测占用，解除占用")



        ListModel{
            id: fileModel
            ListElement{
                fileUrl: "C:\\text.txt"
            }
        }

    ColumnLayout{
        id: mainLayout
        anchors.fill: parent
        spacing: 4

//        Rectangle{
//            anchors.fill: parent
//            color: "green"
//        }

        Label{
            text: qsTr("检测文件")

            Layout.alignment: Qt.AlignTop
            Layout.topMargin: 20
            Layout.leftMargin: 30
        }

        Rectangle{
            Layout.leftMargin: 30
            Layout.rightMargin: 30
            Layout.topMargin: 20
            Layout.preferredHeight: 100
            Layout.fillWidth: true

            ListView{
                id: listFiles

                anchors.fill: parent
                model: fileModel
                delegate: Rectangle {
                    height: 25
                    width: 100
                    Text { text: fileUrl }
                }
            }

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

            color: "blue"
        }

        Rectangle{
            width: 100
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "red"
        }
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
