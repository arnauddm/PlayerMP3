#include "player.hpp"

Player::Player(QObject *parent)
{
    mediaPlayer = new QMediaPlayer();
    musiques = new QVector<QString>;

    isPlaying = false;
    index = 1;
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
#ifdef DEBUG
        qDebug() << musiques->at(i);
#endif
    }

    index = 0;
    mediaPlayer->setMedia(QUrl::fromLocalFile(musiques->at(index)));
}

void Player::precedent(void)
{
    index--;

    if(index < 0)
        index = musiques->size() - 1;

#ifdef DEBUG
    qDebug() << "Index de la musique actuelle : " << index;
#endif

    mediaPlayer->setMedia(QUrl::fromLocalFile(musiques->at(index)));

    if(isPlaying)
        play();
}

void Player::suivant(void)
{
    index++;

    if(index > musiques->size() - 1)
        index = 0;

#ifdef DEBUG
    qDebug() << "Index de la musique actuelle : " << index;
#endif

    mediaPlayer->setMedia(QUrl::fromLocalFile(musiques->at(index)));

    if(isPlaying)
        play();
}

void Player::pause(void)
{
    mediaPlayer->pause();
    isPlaying = false;
}

void Player::play(void)
{
#ifdef DEBUG
    qDebug() << "Play";
#endif
    mediaPlayer->play();
    isPlaying = true;
}

float Player::progression(void)
{
    if(this->loaded() && mediaPlayer->position() > 0)
    {
        float prog = (float)mediaPlayer->position() / (float)mediaPlayer->duration();
        if(prog == 1)
            this->suivant();
        return prog;
    }
    else
    {
        return 0.0;
    }
}

QString Player::piste(void)
{
    if(this->loaded())
    {
        QString piste = musiques->at(index);
        QStringList pisteChemin = piste.split("/");
        QStringList pisteExtension = pisteChemin.at(pisteChemin.size() -1).split(".mp");
        return pisteExtension.at(0);
    }
    else
        return "Musique non chargée";
}

QString Player::piste(const unsigned int index)
{
    QString piste = musiques->at(index);
    QStringList pisteChemin = piste.split("/");
    QStringList pisteExtension = pisteChemin.at(pisteChemin.size() - 1).split(".mp");
    return pisteExtension.at(0);
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

void Player::addMusic(const QList<QUrl> musics)
{
    for(unsigned int i = 0; i < (unsigned int)musics.size(); i++)
    {
#ifdef DEBUG
        qDebug() << musics[i].toString();
#endif
        QString cheminEntierMusique = musics.at(i).toString();
        QStringList cheminMusique = cheminEntierMusique.split("://");
        musiques->push_back(cheminMusique.at(1));
    }
}

QList<QString> Player::allMusiques()
{
    QList<QString> toutesMusiques;
    for(unsigned int i = 0; i < (unsigned int)musiques->size(); i++)
    {
        toutesMusiques.push_back(this->piste(i));
    }

    return toutesMusiques;
}

void Player::setTempsMusique(const float progression)
{
    unsigned int nouveauTemps = progression * mediaPlayer->duration();

#ifdef DEBUG
    qDebug() << "Nouveau temps de lecture : " << nouveauTemps;
#endif

    mediaPlayer->setPosition((qint64)nouveauTemps);
}
