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
Item {
    id: show_map
    objectName: "map"
    visible: true
    height: parent.height
    width: parent.width
    property alias map1 : map1;
    function get_map()
    {
        return map1;
    }
    //绑定鼠标事件
//    MouseArea {
//        anchors.fill: parent
//        onClicked: {
//            Qt.quit();
//        }
//    }
    MyTool{
        id:my_map_tool
    }
    Map {
        id: map1
        objectName: "maptest1"
        anchors.fill: parent
        minimumZoomLevel: 16
        maximumZoomLevel: 19
        zoomLevel: 18
        center:  my_map_tool.wps84_To_Gcj02(30.5594483655,103.9976232481) // QtPositioning.coordinate(30.5594483655,103.9976232481)
        gesture.flickDeceleration:  3000
        // 地图插件
        plugin: Plugin { name: "Gaode" }
    }
    function move(x,y)
    {
        map1.pan(x,y);
    }
    function map_zoom_add(is_add)
    {
        if(is_add==1){
            if(map1.zoomLevel<=map1.maximumZoomLevel){
                map1.zoomLevel+=1;
            }
        }else if(is_add==0)
        {
            if(map1.zoomLevel>=map1.minimumZoomLevel){
                map1.zoomLevel-=1;
            }
        }
    }
    function get_map_width(){
        return map1.width;
    }

}
