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
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QNetworkAccessManager manager;
    auto reply = manager.get(QNetworkRequest{QUrl{argv[1]}});
    reply->readAll();

    QFile xq("myquery.xq");

    QXmlQuery query;
    //query.setQuery("//h1", QUrl{"https://www.youtube.com/results?search_query=cinemasins&page=&utm_source=opensearch"});
    query.setQuery("doc('test_data.xml')//h2");
    QStringList slist;
    query.evaluateTo(&slist);

    foreach (auto s, slist) {
        qDebug() << s;
    }

    auto jsonFile = new QFile("videos.json");
    if (!jsonFile->open(QIODevice::ReadOnly))
        qDebug() << "Could not open videos.json";
    auto jsonRaw = jsonFile->readAll();
    qDebug() << jsonRaw;
    QJsonParseError err;
    auto jsonDocument = QJsonDocument::fromJson(jsonRaw, &err);
    qDebug() << err.error;
    qDebug() << jsonDocument.array().size();
    qDebug() << jsonDocument.array()[0].toObject().keys();
    qDebug() << jsonDocument.array()[1].toObject()["name"];
    qDebug() << QJsonValue(jsonDocument.object()["name"]);
    qDebug() << jsonDocument.object();

    auto videoListModel = new QJsonListModel();
    videoListModel->load(jsonRaw);

    // qmlRegisterType<QJsonModel>("org.qoutuber", "", 1, 0, "QJsonModel");
    qDebug() << "Thats it";
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("videosModel", videoListModel);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
