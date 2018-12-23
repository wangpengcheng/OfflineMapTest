import QtQuick 2.0
import QtQuick.Controls 1.4
import QtMultimedia 5.0
import QtQuick.Layouts 1.2
Item {
    id: video_play_div
    objectName: "video_play_div"
    anchors.fill: parent
    visible: true
    property  url video_path : "file:///C:/Users/lin/Videos/IMG_8983.MOV"
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
                source: video_path
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
                source: video_path
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
                source: video_path
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
                source: video_path
                autoPlay: true
            }
            VideoOutput {
                id: video4
                anchors.fill: parent
                source: mediaPlayer4
            }
        }
    }

}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
