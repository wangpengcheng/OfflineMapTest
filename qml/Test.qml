import QtQuick 2.0

  Rectangle {
      width: 800; height: 800
      color: "#303030"

      Flow {
          anchors.horizontalCenter: parent.horizontalCenter
          anchors.verticalCenter: parent.verticalCenter
//          rows:2
//          columns: 4
         // spacing: 6

          Rectangle { color: "#aa6666"; width: parent*0.2; height: 150 }
          Rectangle { color: "#aaaa66"; width: 50; height: 150 }
          Rectangle { color: "#9999aa"; width: 50; height: 50 }
          Rectangle { color: "#6666aa"; width: 80; height: 50 }
          Rectangle { color: "#aaaa66"; width: 50; height: 150 }
          Rectangle { color: "#9999aa"; width: 50; height: 50 }
          Rectangle { color: "#6666aa"; width: 80; height: 50 }
          Rectangle { color: "#aaaa66"; width: 50; height: 150 }
          Rectangle { color: "#9999aa"; width: 50; height: 50 }
          Rectangle { color: "#6666aa"; width: 80; height: 50 }
      }
  }
