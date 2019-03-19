import QtQuick 2.0
import QtQuick.Window 2.2
import QtLocation       5.3
import QtPositioning    5.3
import QtQuick.Controls 2.4
Window{
        id: control_window
        objectName: "my_control_window"
        visible: true;
        height: 1080;
        width: 1920;
       // title: "控制窗口";
     //   title: "控制窗口"
        Item {
            id: main_div
            anchors.fill: parent
            function get_map1(){
                var map1=MyMap.get_map();
                console.log("<<<<<<"+map1);
            }
            Map {

                id: contrl_show_map
                objectName: "control_show_map"
                anchors.fill: parent
                minimumZoomLevel: 16
                maximumZoomLevel: 19
                zoomLevel: 18
                center: my_map.wps84_To_Gcj02(30.5594483655,103.9976232481)
                gesture.flickDeceleration:  3000
                // 地图插件
                plugin: Plugin { name: "Gaode" }
            }
            Item{
                id:control_div
                x: parent.width*0.6;
                y: parent.height*0.5;
                width: parent.width*0.4;
                height: parent.height*0.5;
                z:1;
//                clip: false
                //transformOrigin: Item.Bottom
                opacity: 1;
                Rectangle{
                    id:back_ground_rectangle
                    color: "#ffffff"
                    clip: true
                    border.width: 2
                    anchors.fill: parent

                    Slider {
                        id: sliderVertical
                        x: parent.width*0.1;
                        y: parent.height*0.2;
                        //width: 60
                        height: parent.height*0.6;
                        width: parent.width*0.1
                        orientation: Qt.Vertical
                    }


                }



            }
            Component.onCompleted: {
               var map_width=my_map.get_map_width();
                console.log(map_width);
            }

        }


}



