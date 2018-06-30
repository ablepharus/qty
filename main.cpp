#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <qjsonmodel.h>
// todo - remove this include
#include <QtNetwork>
#include <QQmlContext>

#include <QtXmlPatterns/QXmlQuery>
#include <QtXmlPatterns/QXmlSerializer>
#include <QXmlQuery>

#include "qjsonlistmodel.h"
#include "videolistmodel.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);


    auto videoListModel = new VideoListModel{};
    // qmlRegisterType<VideoListModel>("org.qoutuber", "", 1, 0, "VideoListModel");
    qDebug() << "Thats it";
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("videosModel", videoListModel);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
