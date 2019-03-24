import QtQuick 2.0
import QtMultimedia 5.0
import QtQuick.Layouts 1.2
Item {
    id:video_item
    //anchors.fill: parent
    visible: true;
    width: {if(parent!=null){parent.width}else{800;}}
    height: {parent?parent.height:800;}
    property string video_path_root: "file:///C:/Users/lin/Videos/out/";
    property  url video_path1 : video_path_root+"yuanshiping.mp4"
    property  url video_path2 : video_path_root+"fenge.mp4"
    property  url video_path3 : video_path_root+"bianyuan.mp4"
    property  url video_path4 : video_path_root+"chedaoxian.mp4"
    property alias media_player: media_player_
    property alias video_out_put: video_out_put_
    MediaPlayer {
        id:media_player_
        source: video_path1
        autoPlay: true
        }
    VideoOutput {
        id:video_out_put_
        anchors.fill: parent
        source: media_player_

    }

    function set_video_source(video_source){
        media_player_.source=video_source;
    }
    function video_source(){
        return media_player_.source
    }
    function video_play(){
        media_player_.play();
    }
    function vido_pause(){
        media_player_.pause();
    }
    function vido_stop(){
        media_player.stop();
    }
    function get_status(){
        return media_player_.status;
    }
    /*
      ToDo:鼠标点击事件
    */
}
