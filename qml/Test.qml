import QtQuick 2.0
Item{
    id:root
    width: {parent?parent.width:800;}
    height: {parent?parent.height:600;}
  Rectangle {
      id:frist_rect
      objectName: "frist_rect"
      anchors.fill: parent
      color: "#303030"

//          anchors.horizontalCenter: parent.horizontalCenter
//          anchors.verticalCenter: parent.verticalCenter
//          rows:2
//          columns: 4
         // spacing: 6

          Rectangle { color: "#aa6666"; width: parent.width*0.2; height: parent.height*0.2 }

      }
      Component.onCompleted: {
          console.log("hello word!!");
          frist_rect.parent=null;
          var my_children=root.children;
          console.log(my_children[0]);
          console.log(frist_rect);
      }
}
