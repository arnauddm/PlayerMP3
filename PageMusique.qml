import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4


Page {
    property string music: []

    FileDialog {
        id: fileDialog
        title: qsTr("Veuillez sélectionner le dossier des musiques")
        selectFolder : false
        selectMultiple: true

        onAccepted:
        {
            //var music;
            player.addMusic(fileDialog.fileUrls);

            /*for(var i = 0; i < fileDialog.fileUrls.length; i++)
            {
                music = music + fileDialog.fileUrls[i] + "\n";
                //music[i] = fileDialog.fileUrls[i].toString();
                //console.log(music[i]);
            }

            musiqueText.text = music;*/

            player.ouvrir();
        }

        onRejected:
        {
        }
    }

    Column {
        Button {
            id: ouvrir
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
