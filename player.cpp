#include "player.hpp"

Player::Player(QObject *parent)
{
    mediaPlayer = new QMediaPlayer();
    musiques = new QVector<QString>;

    isPlaying = false;
    index = 0;
}

void Player::setDossier(const QString dossier)
{
    QStringList cheminDecoupe = dossier.split("://");
    chemin = cheminDecoupe.at(1);
}

void Player::ouvrir(void)
{
    QDir dir(chemin);
    QStringList filtres;
    filtres << "*.mp3" << "*.mp4";
    dir.setNameFilters(filtres);
    QStringList liste = dir.entryList();

    for(unsigned int i = 0; i < (unsigned int)liste.size(); i++)
    {
        musiques->push_back(chemin + "/" + liste.at(i));
        qDebug() << musiques->at(i);
    }

    index = 0;
    mediaPlayer->setMedia(QUrl::fromLocalFile(musiques->at(index)));
}

void Player::precedent(void)
{
    index--;

    if(index < 0)
        index = musiques->size();

    mediaPlayer->setMedia(QUrl::fromLocalFile(musiques->at(index)));
    play();
}

void Player::suivant(void)
{
    index++;

    if(index > musiques->size())
        index = 0;

    mediaPlayer->setMedia(QUrl::fromLocalFile(musiques->at(index)));
    play();
}

void Player::pause(void)
{
    mediaPlayer->pause();
    isPlaying = false;
}

void Player::play(void)
{
    //qDebug() << "Play";
    mediaPlayer->play();
    isPlaying = true;
}

float Player::progression(void)
{
    if(this->loaded())
        return (mediaPlayer->position() / mediaPlayer->duration());
    else
        return 0;
}

QString Player::piste(void)
{
    if(this->loaded())
    {
        QString piste = musiques->at(index);
        QStringList pisteChemin = piste.split("/");
        QStringList pisteExtension = pisteChemin.at(pisteChemin.size() -1).split(".");
        return pisteExtension.at(0);
    }
    else
        return "Musique non chargée";
}

QString Player::tempsTotal(void)
{
    if(this->loaded())
        return convertirTemps(mediaPlayer->duration() / 1000);
    else
        return "0:00";
}

QString Player::tempsActuel(void)
{
    if(this->loaded())
        return convertirTemps(mediaPlayer->position() / 1000);
    else
        return "0:00";
}

bool Player::playing(void)
{
    return isPlaying;
}

QString Player::convertirTemps(const unsigned int temps)
{
    if(temps > 60)
    {
        unsigned int nombreMinute = temps / 60;

        return QString::number(nombreMinute) + ":" + QString::number(temps - (nombreMinute * 60));
    }
    else {
        return "00:" + QString::number(temps);
    }
}

bool Player::loaded()
{
    return musiques->size() == 0 ? false : true;
}
