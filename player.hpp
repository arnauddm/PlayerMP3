#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QObject>
#include <QString>
#include <QMediaPlayer>
#include <QDir>
#include <QUrl>
#include <QVector>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);

    QString convertirTemps(const unsigned int temps);

private:
    QMediaPlayer *mediaPlayer;
    bool isPlaying;
    unsigned int index;
    QVector<QString> *musiques;
    QString chemin;

signals:

public slots:
    void setDossier(const QString dossier);
    void ouvrir(void);
    void precedent(void);
    void suivant(void);
    void pause(void);
    void play(void);

    float progression(void);
    QString piste(void);
    QString tempsTotal(void);
    QString tempsActuel(void);
    bool playing(void);
    bool loaded(void);
};

#endif // PLAYER_HPP
