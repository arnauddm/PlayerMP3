#include "player.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQuickView view;

    Player player;
    view.rootContext()->setContextProperty("player", &player);

    view.setSource(QUrl(QLatin1String("qrc:/main.qml")));


    return app.exec();
}
