import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4


Page {
    FileDialog {
        id: fileDialog
        title: qsTr("Veuillez sélectionner le dossier des musiques")
        selectFolder : false
        selectMultiple: true

        onAccepted:
        {
            player.addMusic(fileDialog.fileUrls);
            player.ouvrir();
        }

        onRejected:
        {
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 40

        Button {
            id: ouvrir
            width: parent.width

            text: qsTr("Ouvrir")

            onClicked:
            {
                fileDialog.open();
            }
        }

        Text {
            id: musiqueText
        }

        ListModel {
            id: dataModel
            //ListElement { titre:"Titre de la musique"; duree:"Indeterminé" }
            //ListElement { titre:"Titre de la musique"; duree:"Indeterminé" }

            //ouvrir.onClicked:
        }

        TableView {
            model: dataModel

            TableViewColumn {
                role: "titre"
                title: "Titre"
                width: 100
            }

            TableViewColumn {
                role: "duree"
                title: "Durée"
                width: 50
            }
        }
    }
}
