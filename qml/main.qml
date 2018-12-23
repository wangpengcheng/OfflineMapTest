//import QtQuick 2.6
//import QtQuick.Window 2.2

//Window {
//    visible: true
//    width: 640
//    height: 480
//    title: qsTr("Hello World")

//    MainForm {
//        anchors.fill: parent
//        mouseArea.onClicked: {
//            console.log(qsTr('Clicked on background. Text: "' + textEdit.text + '"'))
//        }
//    }
//}
import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.5
import QtLocation       5.3
import QtPositioning    5.3
import QtQml 2.0
import QtWebEngine 1.0
Item {
    id: main
    objectName: "main"
    visible: true
    height: 1080*1
    width: 1920*1

    Column {
        anchors.fill: parent
        spacing: 0
        Item {
            id: item1
            height: parent.height*0.7
            width: parent.width
            MyMap{}//添加地图
        }
        Item {
            id: rol
            height: parent.height*0.3
            width: parent.width

            Row{
                id: row1
                spacing: 1
                height: parent.height
                width: parent.width
                Rectangle {
                    id: re2
                    height: parent.height
                    width: parent.width*0.25
                }
                Item {
                    height: parent.height
                    width: parent.width*0.25
                     DashBoard{}
                }

            }
        }
    }
}

