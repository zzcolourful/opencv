//import QtQuick 2.12
//import QtQuick.Window 2.12
//import MyModule 1.0

import QtQuick 2.12
import QtQuick.Controls 2.12
import MyModule 1.0

ApplicationWindow {

    id: mainWindow
        width: 800
        height: 600
        title: "QML + C++ Drawing Board"
        visible: true

        Board{
            id: drawingView
            anchors.fill: parent
            focus: true
        }
        Button{
            text: "LoadImage"
            onClicked: {
                Board.loadImage("")
            }
        }



}
