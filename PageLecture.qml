import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2

Page {
    Timer {
        interval: 100;
        running: true;
        repeat: true;

        onTriggered:
        {
            titreMusique.text = player.piste();
            tempsActuelMusique.text = player.tempsActuel();
            tempsTotalMusique.text = player.tempsTotal();
            progressBar.value = player.progression();
        }
    }

    Column {
        spacing: 20
        anchors.centerIn: parent
        id: root

        Image {
            id: image
            visible: true
            fillMode: Image.PreserveAspectFit
            width: (parent.width / 5) * 3
            source: "qrc:/icone/music.png"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Row {
            spacing: 20
            anchors.horizontalCenter: parent.horizontalCenter

            Image {
                id: retour
                source: "qrc:/icone/previous.png"
                height: 50
                fillMode: Image.PreserveAspectFit
                anchors.verticalCenter: parent.verticalCenter

                MouseArea {
                    anchors.fill: parent

                    onClicked:
                    {
                        if(player.loaded())
                        {
                            player.precedent();
                        }
                    }
                }
            }

            Image {
                id: playAndPause
                height: 70
                fillMode: Image.PreserveAspectFit
                anchors.verticalCenter: parent.verticalCenter
                source: "qrc:/icone/play.png"

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        if(player.loaded())
                        {
                            if(player.playing())
                            {
                                player.pause();
                                parent.source = "qrc:/icone/play.png";
                            }
                            else
                            {
                                player.play();
                                parent.source = "qrc:/icone/pause.png";
                            }
                        }
                        else
                        {
                            parent.source = "qrc:/icone/play.png";
                        }
                    }
                }
            }

            Image {
                id: suivant
                anchors.verticalCenter: parent.verticalCenter
                source: "qrc:/icone/next.png"
                height: 50
                fillMode: Image.PreserveAspectFit

                MouseArea {
                    anchors.fill: parent

                    onClicked:
                    {
                        if(player.loaded())
                        {
                            player.suivant();
                        }
                    }
                }
            }
        }

        Row {
            id: bandeauLecture
            spacing: 10
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                id: tempsActuelMusique
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("0:00");
            }

            ProgressBar {
                id: progressBar
                anchors.verticalCenter: parent.verticalCenter
                height: 10
            }

            Text {
                id: tempsTotalMusique
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("0:00");
            }
        }

        Text {
            id: titreMusique
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Musique non chargée")
        }
    }
}
