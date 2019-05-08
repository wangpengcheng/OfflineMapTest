
import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.5
import QtLocation       5.3
import QtPositioning    5.3
import QtQml 2.0
import QtMultimedia 5.0
Item {
    id: main_show_window
    objectName: "main_show_window"
    visible: true
//    height: 1080*1
//    width: 1920*1
    property alias my_map : show_map;
    MyTool{
        id:my_tool0
    }
    Item {
        id: map_item
        height: parent.height
        width: parent.width
        z: 0
        Map {
            id: show_map
            objectName: "show_map"
            anchors.fill: parent
            minimumZoomLevel: 16
            maximumZoomLevel: 19
            zoomLevel: 18
            center:   my_tool0.wps84_To_Gcj02(30.6327442500,104.0812481500);//my_tool0.wps84_To_Gcj02(30.5594483655,103.9976232481) // my_tool.wps84_To_Gcj02()
            gesture.flickDeceleration:  3000
            // 地图插件
            plugin: Plugin { name: "Gaode" }
            MouseArea{
                anchors.fill: parent
                width: parent.width
                height: parent.height
            }
        }
    }
//    Item { //播放栏
//        id :video_play_item
//        visible: false
//        objectName: "video_play_item"
//        height: parent.height*0.7
//        width: parent.width*0.5
//        VideoPlay{
//            id: my_video_play;
//        }//视频播放模块
//    }
    //控制窗口
    //MainShowWindow{}
    //底部数据显示栏
//    Item {
//         id: rol
//         height: parent.height*0.3
//         opacity: 0.7
//         visible: true
//         anchors.bottom: parent.bottom
//         anchors.bottomMargin: 5
//         width: parent.width

//         Row{
//             id: row1
//             spacing: 1
//             height: parent.height
//             width: parent.width
//             Rectangle {
//              id: re2
//              height: parent.height
//              width: parent.width*0.25
//              SpeedChart{
//                  id: my_speed_chart;
//              }

//             }
//             Item {
//               height: parent.height
//               width: parent.width*0.25
//               DashBoard{
//                   id: my_dash_borad;
//               }
//             }
//          }
//        }
    //控制窗口
    //ControlWindow{}
    //设置键盘监听事件
//    Item {
//        focus: true;            // 此句是必须的, 否则没有功能
//        Keys.enabled: true;
//        Keys.onEscapePressed: {
//            Qt.quit();  // 没有功能: 不退出, why?
//        }
//        //var map1=my_map.my_map;
//        //键盘点击事件
//        Keys.onPressed: {
//            console.log("This click key  is "+event.key);
//            //显示视频
////            if ((event.modifiers & Qt.ControlModifier ) && //ctrl+shift+v
////                (event.modifiers & Qt.AltModifier )&&
////                (event.key == Qt.Key_V)){
////                if(video_play_item.visible==false)
////                {
////                    video_play_item.visible= true;
////                    //my_video_play.video_play();
////                }else{
////                    video_play_item.visible= false;
////                    //my_video_play.video_pause();
////                }
////            }
//            //显示仪表盘
//            if ((event.modifiers & Qt.ControlModifier) && //ctrl+shift+c
//                (event.modifiers & Qt.AltModifier )&&
//                (event.key == Qt.Key_C)){
//                if(row1.visible==false)
//                {
//                    row1.visible=true;
//                }else{
//                    row1.visible=false;
//                }
//            }
//            switch(event.key) {
//             //基本控制-start
//                //方向控制-start
//            case 16777234:
//                my_map.move(-10,0);//左移
//                break;
//            case 16777235:
//                my_map.move(0,-10);//上移
//                break;
//            case 16777236:
//                my_map.move(10,0);//右移
//                break;
//            case 16777237:
//                 my_map.move(0,10);//下移
//                break;
//                //方向控制-end
//              //缩放-start
//            case 43://小键盘“+”
//                my_map.map_zoom(1);
//                break;
//            case 45://小键盘“-”
//                my_map.map_zoom(0);
//                break;

//             //缩放-end
//            default:
//                console.log("This click key  is "+event.key);
//                break;
//            }
//        }
//    }
}



