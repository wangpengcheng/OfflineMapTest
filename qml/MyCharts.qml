
import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.5
import QtLocation       5.3
import QtPositioning    5.3
import QtQml 2.0
import QtMultimedia 5.0

Item {
     id: rol
     //height: 1080*0.3
     opacity: 0.7
     visible: true
//     anchors.bottom: parent.bottom
//     anchors.bottomMargin: 5
    // width: 1920

     Row{
         id: row1
         spacing: 1
         height: parent.height
         width: parent.width
         Rectangle {
          id: re2
          height: parent.height
          width: parent.width*0.5
          SpeedChart{
              id: my_speed_chart;
          }

         }
         Item {
           height: parent.height
           width: parent.width*0.5
           DashBoard{
               id: my_dash_borad;
           }
         }
      }
}
