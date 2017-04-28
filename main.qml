import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import one.chchy.FDService 1.0

ApplicationWindow {
    id: idMainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("检测占用，解除占用")

    Rectangle{
        id: idprogressBar
        anchors.fill: parent
        color: Qt.rgba(0.5, 0.5, 0.5, 0.5)
        visible: false

        ProgressBar{
            anchors.centerIn: parent
            indeterminate: true

//            value: slider.value
//            style: ProgressBarStyle {
//                background: Rectangle {
//                    radius: 2
//                    color: "lightgray"
//                    border.color: "gray"
//                    border.width: 1
//                    implicitWidth: 200
//                    implicitHeight: 24
//                }
//                progress: Rectangle {
//                    color: "lightsteelblue"
//                    border.color: "steelblue"
//                }
//            }
        }

        z: 10
    }

    FDService{
        id: fdObject
        onComplete: {
            for (var index in filePaths){
                console.log(filePaths[index]);
                progressModel.append({
                                      "progressInfo" : filePaths[index]
                                     })
            }

            idprogressBar.visible = false;
        }

        onUnlock: {
            idprogressBar.visible = false;
        }

        onDelcomplete: {

        }

        onCrush: {

        }
    }

    ListModel{
        id: fileModel
        ListElement{
            fileUrl: "C:\\text.txt"
        }
        ListElement{
            fileUrl: "E:\\UBuntu1404.rar"
        }
        ListElement{
            fileUrl: "H:\\CloudMusic\\MONACA - クロイウタ／日本国外向け製品収録版.mp3"
        }
    }

    ListModel{
        id: progressModel
    }

//    Component{
//        id: idFileUrl
//        Item {
//            id: fileurldelegate
//            width: parent.width
//            height: 30

//            MouseArea{
//                anchors.fill: parent
//                onClicked: fileurldelegate.ListView.view.currentIndex = index
//            }

//            RowLayout{
//                anchors.left: parent.left
//                anchors.verticalCenter: parent.verticalCenter
//                spacing: 8
//                Text{
//                    id: id_fileurl
//                    text: fileUrl
//                    color: fileurldelegate.ListView.isCurrentItem ? "red" : "black"
//                    font.pixelSize: fileurldelegate.ListView.isCurrentItem ? 22 : 18
//                    Layout.fillWidth: true
//                }
//            }
//        }
//    }

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
                clip: true
//                delegate: Rectangle {
//                    height: 25
////                    width: 100
//                    Text { text: fileUrl }
//                }

                delegate: FileUrlDelegate{}

                highlight: Rectangle{
                    color: "lightblue"
                }
            }

            border.color: "black"

            DropArea{
                anchors.fill: parent
                onDropped: {
//                    console.log("mytext:" + drop.text)
                    if (drop.hasUrls){
                        for (var i = 0; i < drop.urls.length; ++i){
//                            var regexp = new RegExp("/", "g");
                            var fileurl = drop.urls[i].substr(8).replace(/\//g, "\\");
//                            console.log("myText:" + fileurl);

                            listFiles.model.append({
                                                       "fileUrl" : fileurl
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
                clip: true
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
                        idprogressBar.visible = true;
                    }
                }
            }

            Button{
                text: "解锁"
                onClicked: {
                    if (listFiles.currentIndex >= 0){
                        var fileUrl = fileModel.get(listFiles.currentIndex).fileUrl
                        console.log(fileUrl)
                        fdObject.unlockHandle(fileUrl)
                        idprogressBar.visible = true;
                    }
                }
            }

            Button{
                text: "删除"
                onClicked: {

                }
            }

            Button{
                text: "粉碎"
                onClicked: {

                }
            }

            Button{
                text: "取消"
                onClicked: {
                    idMainWindow.close();
                }
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
