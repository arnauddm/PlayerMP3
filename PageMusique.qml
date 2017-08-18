import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Dialogs 1.2

Page {
    FileDialog {
        id: fileDialog
        title: qsTr("Veuillez sélectionner le dossier des musiques")
        selectFolder : true
        selectMultiple: false

        onAccepted:
        {
            player.setDossier(fileDialog.folder);
            player.ouvrir();
        }

        onRejected:
        {
        }
    }

    Button {
        id: ouvrir
        text: qsTr("Ouvrir")

        onClicked:
        {
            fileDialog.open();
        }
    }
}
