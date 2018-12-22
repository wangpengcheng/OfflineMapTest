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
ApplicationWindow {
    id: main
    objectName: "main"
    visible: true
    height: 1080*1
    width: 1920*1

    Item {
        id: div1
        objectName:"div1"

    }
    MyMap{}//添加地图
    Window{
        id: window1
        objectName: "window1"
        visible: true
        width: 500
        height: 500
        DashBoard{}
    }

}
