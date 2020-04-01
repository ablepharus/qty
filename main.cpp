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
#include "videoplayer.h"
#include "playlist.h"

#include <VLCQtCore/Common.h>
#include <VLCQtCore/MediaList.h>
#include <VLCQtQml/QmlVideoPlayer.h>
#include <VLCQtQml/QmlPlayer.h>
#include <VLCQtQml/QmlVideoOutput.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>

//class VlcQmlMediaListPlayer;
//class QVP : public VlcQmlPlayer
//{
//    friend class VlcQmlMediaListPlayer;
//};

//class VlcQmlMediaListPlayer : public QObject
//{
//    Q_OBJECT
//public:
//    VlcQmlMediaListPlayer(QVP *p)
//    {
//        qP = p;
//        mL = new VlcMediaListPlayer{p->_player, p->_instance};
//    }
//protected:
//    VlcMediaListPlayer *mL;
//    QVP *qP;
//};

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QCoreApplication::setOrganizationName("ableph");
    QCoreApplication::setOrganizationDomain("ableph.net");
    QCoreApplication::setApplicationName("qYT");

    //VlcInstance vlcInstance{QStringList{VlcCommon::args()} << "--verbose=5"
    //                        << "--http-user-agent=Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36"};
    //auto mediaListPlayer = new VlcMediaListPlayer{&vlcInstance};

    //qDebug()    << VlcCommon::setPluginPath("/usr/lib/vlc/lua/playlist/")
    //            << VlcCommon::args();
    //VlcQmlVideoPlayer::registerPlugin();
    //

    //auto mediaList = new VlcMediaList{&vlcInstance};
    //auto _lm = libvlc_media_new_location(vlcInstance.core(), _video);
    //libvlc_media_slaves_add(_lm, libvlc_media_slave_type_audio, 0, _audio);
    //mediaList->addMedia(new VlcMedia{_lm});
    //auto mf = new VlcMedia{"http://youtube.com/watch?v=I6HQqlJWWH0", false, &vlcInstance};
    //mediaList->addMedia(new VlcMedia{"/home/ablepharus/vid.mkv", true,  &vlcInstance});
    //mediaList->addMedia(mf);
    //mediaList->addMedia(mf2);
    //mediaListPlayer->setMe

    //vlcPl.setPlayer(mediaListPlayer->mediaPlayer());
    //vlcPl.setUrl({"http://youtube.com/watch?v=I6HQqlJWWH0"});
    //vlcPl.setAutoplay(true);
    //vlcPl.play();
    qDebug() << "" //mediaListPlayer->mediaPlayer()->dumpObjectInfo()
             << ""//mediaListPlayer-p>mediaPlayer()->video()->dumpObjectInfo()
             << "AAAAA" //mediaListPlayer->mediaPlayer()->video()->dumpObjectTree()
             << "" ;//mediaListPlayer->mediaPlayer()->video()->trackDescription();

    YoutubeDl ytService{};
    auto videoListModel = new VideoListModel{};
    auto videoPlayer = new YoutubePlayer{};
    qmlRegisterType<Playlist>("org.qoutuber", 1, 0, "Playlist");
    qmlRegisterType<VideoListModel>("org.qoutuber", 1, 0, "VideoListModel");
    qDebug() << "Thats it";
    QQmlApplicationEngine engine;
    //((VlcQmlSource*) engine.rootContext()->property("m_vp").data())->setPlayer(mediaListPlayer->mediaPlayer());

    engine.rootContext()->setContextProperty("videosModel", videoListModel);
    engine.rootContext()->setContextProperty("videoPlayer", videoPlayer);
    //engine.rootContext()->setContextProperty("mediaList", mediaList);
    //engine.rootContext()->setContextProperty("vlcPlayer", &vlcPl);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    //mediaListPlayer->play();

    return app.exec();
}
