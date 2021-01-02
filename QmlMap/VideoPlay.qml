import QtQuick 2.0
import QtQuick.Controls 1.4
import QtMultimedia 5.0
import QtQuick.Layouts 1.2
Item {
    id: video_play_div
    objectName: "video_play_div"

    anchors.fill: parent
    visible: true
    property string video_path_root: "file:///C:/Users/lin/Videos/out/";

    property  url video_path1 : video_path_root+"yuanshiping.mp4"
    property  url video_path2 : video_path_root+"fenge.mp4"
    property  url video_path3 : video_path_root+"bianyuan.mp4"
    property  url video_path4 : video_path_root+"chedaoxian.mp4"
    property real video_width: parent.width*0.5
    property real video_height: parent.height*0.5

    Grid {
        columns: 2
        spacing: 2
        Rectangle {
            id: video_paly1
            width: video_width;
            height: video_height;
            MediaPlayer {
                id: mediaPlayer1
                source: video_path1
                autoPlay: true
            }
            VideoOutput {
                id: video1
                anchors.fill: parent
                source: mediaPlayer1
            }
        }
        Rectangle {
            id: video_paly2
            width: video_width;
            height: video_height;
            MediaPlayer {
                id: mediaPlayer2
                source: video_path2
                autoPlay: true
            }
            VideoOutput {
                id: video2
                anchors.fill: parent
                source: mediaPlayer2
            }
        }
        Rectangle {
            id: video_paly3
            width: video_width;
            height: video_height;
            MediaPlayer {
                id: mediaPlayer3
                source: video_path3
                autoPlay: true
            }
            VideoOutput {
                id: video3
                anchors.fill: parent
                source: mediaPlayer3
            }
        }
        Rectangle {
            id: video_paly4
            width: video_width;
            height: video_height;
            MediaPlayer {
                id: mediaPlayer4
                source: video_path4
                autoPlay: true
            }
            VideoOutput {
                id: video4
                anchors.fill: parent
                source: mediaPlayer4
            }
        }
    }
    //隐藏显示div
    function isVisiable()
    {
        video_play_div.visible=!video_play_div.visible;
    }
    //设置div宽和高
    function set_width(new_width)
    {
        video_play_div.width=new_width;
    }
    function set_height(new_height)
    {
        video_play_div.height=new_height;
    }
    function video_play()
    {
        mediaPlayer1.play();
        mediaPlayer2.play();
        mediaPlayer3.play();
        mediaPlayer4.play();
    }
    function video_pause()
    {
        mediaPlayer1.pause();
        mediaPlayer2.pause();
        mediaPlayer3.pause();
        mediaPlayer4.pause();
    }
    function video_stop()
    {
        mediaPlayer1.stop();
        mediaPlayer2.stop();
        mediaPlayer3.stop();
        mediaPlayer4.stop();
    }


}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
