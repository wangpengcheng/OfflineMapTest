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
import QtMultimedia 5.0
Item {
    id: main
    objectName: "main"
    visible: true
    height: 1080*1
    width: 1920*1
    Item {
        id: map_item
        height: parent.height
        width: parent.width
        z: 0
        MyMap{
            id:my_map
        }//添加地图
    }
    Item { //播放栏
        id :video_play_item
        objectName: "video_play_item"
        height: parent.height*0.7
        width: parent.width*0.5
        VideoPlay{}//视频播放模块
    }

    //底部数据显示栏
    Item {
         id: rol

         height: parent.height*0.3
         opacity: 0.7
         visible: true
         anchors.bottom: parent.bottom
         anchors.bottomMargin: 10
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
    //控制窗口
    //ControlWindow{}
    //设置键盘监听事件
    Item {
        focus: true;            // 此句是必须的, 否则没有功能
        Keys.enabled: true;
        Keys.onEscapePressed: {
            Qt.quit();  // 没有功能: 不退出, why?
        }
        //var map1=my_map.my_map;
        //键盘点击事件
        Keys.onPressed: {
            console.log("This click key  is "+event.key);
            switch(event.key) {
             //基本控制-start
                //方向控制-start
            case 16777234:
                my_map.move(-10,0);//左移
                break;
            case 16777235:
                my_map.move(0,-10);//上移
                break;
            case 16777236:
                my_map.move(10,0);//右移
                break;
            case 16777237:
                 my_map.move(0,10);//下移
                break;
                //方向控制-end
              //缩放-start
            case 43://小键盘“+”
                map1.zoomLevel+=1;
                break;
            case 45://小键盘“-”
                map1.zoomLevel-=1;
                break;

             //缩放-end
            default:
                console.log("This click key  is "+event.key);
                break;
            }
        }
    }
}

