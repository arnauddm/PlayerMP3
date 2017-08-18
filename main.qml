import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Lecteur MP3")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

       PageLecture {
           id: pageLecture
       }

       PageMusique {
            id: pageMusique
       }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Lecure")
        }
        TabButton {
            text: qsTr("Musiques")
        }
    }
}
