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
import QtQuick 2.0
import QtQuick.Window 2.2
import QtLocation       5.3
import QtPositioning    5.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.0
Item{
    id: control_window
    objectName: "my_control_window"
    visible: true;
    height: 1080;
    width: 1920;
    // title: "控制窗口";
    //   title: "控制窗口"
    //主要显示窗口
    MainShowWindow{
        id:main_window
    }
    MyTool {
        id:my_tool
    }
    Item {
        id: main_div
        anchors.fill: parent
//        MapContrlModel{
//        }
        MapContrlModel{
            id: map_control_model
            objectName: "map_control_model"
        }
        //设置键盘监听
           focus:true;            // 此句是必须的, 否则没有功能
            //anchors.fill: parent
            width: parent.width
            height: parent.height
            Keys.enabled: true;
            z:10;
            Keys.onEscapePressed: {
                Qt.quit();  // 没有功能: 不退出, why?
            }
            //键盘点击事件
            Keys.onPressed: {
                console.log("This click key  is "+event.key);
                var contrl_show_map= map_control_model.control_show_map;
                //显示视频
    //            if ((event.modifiers & Qt.ControlModifier ) && //ctrl+shift+v
    //                (event.modifiers & Qt.AltModifier )&&
    //                (event.key == Qt.Key_V)){
    //                if(video_play_item.visible==false)
    //                {
    //                    video_play_item.visible= true;
    //                    //my_video_play.video_play();
    //                }else{
    //                    video_play_item.visible= false;
    //                    //my_video_play.video_pause();
    //                }
    //            }
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
                switch(event.key) {
                 //基本控制-start
                    //方向控制-start
                case 16777234:
                    //my_map.move(-10,0);//左移
                    map_control_model.map_move(2);
                    break;
                case 16777235:
                    //my_map.move(0,-10);//上移
                    map_control_model.map_move(1);
                    break;
                case 16777236:
                    //my_map.move(10,0);//右移
                    map_control_model.map_move(3);
                    break;
                case 16777237:
                     //my_map.move(0,10);//下移
                    map_control_model.map_move(4);
                    break;
                    //方向控制-end
                  //缩放-start
                case 43://小键盘“+”
                    //my_map.map_zoom(1);
                    map_control_model.map_updown(1);
                    break;
                case 45://小键盘“-”
                    //my_map.map_zoom(0);
                   map_control_model.map_updown(2);
                    break;

                 //缩放-end
                default:
                    console.log("This click key  is "+event.key);
                    break;
                }
            }

    }


}
