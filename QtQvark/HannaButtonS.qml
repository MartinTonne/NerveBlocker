import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Button {
    id: dustepus
    text: qsTr("Default")
    height: applicationWindow1.height/8
    anchors.rightMargin: 0
    anchors.leftMargin: 0
    anchors.left: parent.left
    anchors.right: parent.right 
    style: ButtonStyle {
        background: Rectangle{
            gradient: Gradient {
                 GradientStop { position: 0.0; color: dustepus.pressed ? "#800000" : "#ff4040"}
                 GradientStop { position: 1.0; color: dustepus.pressed ? "#bf0000" :  "#ff8080"}
            }
        }
    }


}
