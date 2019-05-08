import QtQuick 2.0
import QtQuick.Window 2.2
import QtLocation       5.3
import QtPositioning    5.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.0

Item{
    visible: true
//    height: 1080//parent.height
//    width: 1920//parent.width
    //anchors.fill: parent
    property real move_dx: 10//pixels
    property real map_scale_x: 4
    property real map_scale_y: 3
    property alias control_show_map: contrl_show_map
    //property alias control_div: control_div
    MyTool{
        id:my_tool2
    }
    Map {
        id: contrl_show_map
        objectName: "control_show_map"
        anchors.fill: parent
        minimumZoomLevel: 16
        maximumZoomLevel: 19
        zoomLevel: 18
        center:   my_tool2.wps84_To_Gcj02(30.6327442500,104.0812481500);//my_tool2.wps84_To_Gcj02(30.5594483655,103.9976232481) // my_tool.wps84_To_Gcj02()
        gesture.flickDeceleration:  3000
        // 地图插件
        plugin: Plugin { name: "Gaode" }
        MouseArea{
            anchors.fill: parent
            width: parent.width
            height: parent.height
        }
    }

    Item{
        id:control_div
        x: parent.width*0.6;
        y: parent.height*0.5;
        width: parent.width*0.4;
        height: parent.height*0.5;
        anchors.right: parent.right
        anchors.bottom:parent.bottom
        anchors.rightMargin: parent.width*0.05
        z:1;
        anchors.bottomMargin: parent.height*0.05
        //                clip: false
        //transformOrigin: Item.Bottom
        opacity: 0.8;
        Rectangle{
            id:back_ground_rectangle
            color: "#f9f8f8"
            radius: 15
            clip: true
            border.width: 2
            anchors.fill: parent
            Item {
                id: row
                anchors.fill: parent
                width: parent.width
                height: parent.height
    //                    anchors.verticalCenter: parent.verticalCenter
    //                    anchors.horizontalCenter: parent.horizontalCenter
                Item{
                    id:move_div
                    width: parent.width*0.5
                    height: parent.height*0.8
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width*0.05
                    anchors.verticalCenter: parent.verticalCenter
                    //anchors.top: row.top
                    property string fangxiang_pic: "qrc:/img/Control/fangxiang.png";
                    property string fangxiang_pic1: "qrc:/img/Control/fangxiang_1.png";
                    Item{
                        id:move_top
                        //anchors.fill: parent
                        width: parent.width*0.8
                        height: parent.height*0.25
                        Button{
                            id:move_top_button
                            display: AbstractButton.IconOnly
                         //   anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            //anchors.top: parent.top;
                            //anchors.topMargin: parent.height*0.5*0.2;
                            width: parent.width*0.25
                            height: parent.width*0.25
                            anchors.verticalCenter: parent.verticalCenter

                            //anchors.fill: parent
                            background:Image {
                                    width: parent.width
                                    height: parent.height
                                    anchors.fill: parent
                                    source:{
                                        if(parent.hovered) {
                                            move_div.fangxiang_pic1;
                                        } else{
                                            move_div.fangxiang_pic;
                                        }
                                    }
                                    rotation: 180
                                    }
                            onClicked: {
                               map_move(1);
                            }


                        }
                    }
                    Item{
                        id:move_left_right
                        //anchors.fill: parent
                        width: parent.width*0.8
                        height: parent.height*0.25
                       // anchors.horizontalCenter: parent.horizontalCenter
                       anchors.top:move_top.bottom
                       //anchors.topMargin: parent.height*0.15
                        Button {
                            id:move_left_button
                            display: AbstractButton.IconOnly
                            anchors.verticalCenter: parent.verticalCenter
                            //anchors.horizontalCenter: parent.horizontalCenter
                            anchors.left: parent.left;
                            anchors.leftMargin: parent.width*0.5*0.1;
                            width: parent.width*0.25
                            height: parent.width*0.25
                            clip: false
                            visible: true
                            font.pointSize: 7
                            focusPolicy: Qt.NoFocus

                            antialiasing: false
                            // anchors.fill: parent
                            background:Image {
                                    width: parent.width
                                    height: parent.height
                                    anchors.fill: parent
                                    source:{
                                        if(parent.hovered) {
                                            move_div.fangxiang_pic1;
                                        } else{
                                            move_div.fangxiang_pic;
                                        }
                                    }
                                    rotation: 90
                                    }
                            onClicked: {
                                map_move(2);
                            }

                        }
                        Button {
                            id:move_right_button
                            display: AbstractButton.IconOnly
                            anchors.verticalCenter: parent.verticalCenter
                            //anchors.horizontalCenter: parent.horizontalCenter
                            anchors.right: parent.right;
                            anchors.rightMargin: parent.width*0.5*0.1;

                            width: parent.width*0.25
                            height: parent.width*0.25
                            //anchors.fill: parent
                            background:Image {
                                    width: parent.width
                                    height: parent.height
                                    anchors.fill: parent
                                    source: {
                                        if(parent.hovered) {
                                            move_div.fangxiang_pic1;
                                        } else{
                                            move_div.fangxiang_pic;
                                        }
                                    }
                                    rotation: 270
                                    }
                            onClicked: {
                                map_move(3);
                            }

                        }
                    }
                    Item{
                        id:move_bottom
                        //anchors.fill: parent
                        width: parent.width*0.8
                        height: parent.height*0.25
                        //anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top:move_left_right.bottom
                        Button{
                            id:move_bottom_button
                            display: AbstractButton.IconOnly
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            //anchors.top: parent.top;
                            //anchors.topMargin: parent.height*0.5*0.2;
                            width: parent.width*0.25
                            height: parent.width*0.25
                            //anchors.fill: parent
                            background:Image {
                                    width: parent.width
                                    height: parent.height
                                    //anchors.fill: parent
                                    source:{
                                        if(parent.hovered) {
                                            move_div.fangxiang_pic1;
                                        } else{
                                            move_div.fangxiang_pic;
                                        }
                                    }
                                    rotation: 0
                                    }
                            onClicked: {
                                map_move(4);
                            }

                        }
                    }
                    Item{

                        id:text_col
                        width: parent.width*0.8
                        height: parent.height*0.1
                        //anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top:move_bottom.bottom
                        Label {
                            id: text1
                            width: parent.width
                            height: parent.height

                            text: qsTr("地图平移")
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.topMargin: 26
                            verticalAlignment: Text.AlignVCenter
                            font.bold: true
                            fontSizeMode: Text.Fit
                            horizontalAlignment: Text.AlignHCenter
                            font.pixelSize: 22
                        }

                    }
                }
                Item{
                    id:slider_col
                    width:parent.width*0.2
                    height: parent.height*0.8
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: move_div.right
                    //anchors.leftMargin: move_div.width*0.2
                    Slider {
                        id: sliderVertical
                        //width: 60
                       // anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        focusPolicy: Qt.NoFocus
                        anchors.top: parent.top
                        anchors.topMargin: parent.height*0.08
                        height: parent.height*0.6;
                        width: parent.width*0.5
                        orientation: Qt.Vertical
                        from :0;
                        to:10;
                        value: 3
                    }

                    Label {
                        id: text2
                        width: parent.width
                        height: parent*0.3
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: sliderVertical.bottom
                        anchors.topMargin: sliderVertical.height*0.1
                        text: qsTr("平移\n速度")
                        verticalAlignment: Text.AlignVCenter
                        font.bold: true
                        fontSizeMode: Text.Fit
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: 22
                    }
                }
                Item{
                    id:up_col
                    width: parent.width*0.2;
                    height: parent.height*0.8;
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: slider_col.right
                    anchors.rightMargin:10

                    property string locate_pic: "qrc:/img/Control/dingwei.png"
                    property string up_pic: "qrc:/img/Control/fangda.png"
                    property string down_pic: "qrc:/img/Control/suoxiao.png"
                    property string locate_pic1: "qrc:/img/Control/dingwei_1.png"
                    property string up_pic1: "qrc:/img/Control/fangda_1.png"
                    property string down_pic1: "qrc:/img/Control/suoxiao_1.png"
                    Button{
                        id:map_local
                        display: AbstractButton.IconOnly
                        //anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top;
                        anchors.topMargin: parent.height*0.5*0.2;
                        width: parent.width*0.5
                        height: parent.width*0.5
                        //anchors.fill: parent
                        background:Image {
                                width: parent.width
                                height: parent.height
                                anchors.fill: parent
                                source:{
                                    if(parent.hovered) {
                                        up_col.locate_pic1;
                                    } else{
                                        up_col.locate_pic;
                                    }
                                }
                                }
                        onClicked: {
                            contrl_show_map.center=my_tool2.wps84_To_Gcj02(30.5594483655,103.9976232481);
                            contrl_show_map.zoomLevel=18;
                           // main_window.my_map.map1.center=contrl_show_map.center;
                           // main_window.my_map.map1.zoomLevel=contrl_show_map.zoomLevel;
                        }
                    }
                    Button{
                        id:map_up
                        display: AbstractButton.IconOnly
                        //anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: map_local.bottom
                        anchors.topMargin: 10
                        width: parent.width*0.5
                        height: parent.width*0.5
                        //anchors.fill: parent
                        background:
                            Image {
                                width: parent.width
                                height: parent.height
                                anchors.fill: parent
                                source:{
                                    if(parent.hovered) {
                                        up_col.up_pic1;
                                    } else{
                                        up_col.up_pic;
                                    }
                                }
                            }
                        onClicked: {
                            map_updown(1);
                        }


                    }
                    Button{
                        id:map_down
                        display: AbstractButton.IconOnly
                        //anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: map_up.bottom
                        anchors.topMargin: 10
                        width: parent.width*0.5
                        height: parent.width*0.5
                        //anchors.fill: parent
                        background:Image {
                                width: parent.width
                                height: parent.height
                                anchors.fill: parent
                                source:{
                                    if(parent.hovered) {
                                        up_col.down_pic1;
                                    } else{
                                        up_col.down_pic;
                                    }
                                }
                        }
                        onClicked: {
                            map_updown(2);
                        }

                    }
                    Label {
                        id: text3
                        width: parent.width
                        height: parent*0.3
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: map_down.bottom
                        anchors.topMargin:  sliderVertical.height*0.1
                        text: qsTr("地图\n缩放")
                        verticalAlignment: Text.AlignVCenter
                        font.bold: true
                        fontSizeMode: Text.Fit
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: 22
                    }

                }
            }

        }
    }
    /*
     *move_model 1 :top,2 :left ,3:right 4:bottom
    */
    function map_move(move_model){
        switch(move_model){
        case 1 :
            contrl_show_map.pan(0,-move_dx*sliderVertical.value);
            //main_window.my_map.map1.pan(0,-move_dx*sliderVertical.value*map_scale_y);
            break;
        case 2:
            contrl_show_map.pan(-move_dx*sliderVertical.value,0);
            //main_window.my_map.map1.pan(-move_dx*sliderVertical.value*map_scale_x,0);
            break;
        case 3:
            contrl_show_map.pan(move_dx*sliderVertical.value,0);
            //main_window.my_map.map1.pan(move_dx*sliderVertical.value*map_scale_x,0);
            break;
        case 4:
            contrl_show_map.pan(0,move_dx*sliderVertical.value);
            //main_window.my_map.map1.pan(0,move_dx*sliderVertical.value*map_scale_y);
            break;
        default:
            console.log("input error");
            break;
        }

    }
    /*
      map_mode 1 :up,2:down
    */
    function map_updown(map_model){
        if(map_model===2){
            contrl_show_map.zoomLevel-=1;
           // main_window.my_map.map1.zoomLevel-=1;
        }else if(map_model===1){
            contrl_show_map.zoomLevel+=1;
          //  main_window.my_map.map1.zoomLevel+=1;
        }
    }

}
