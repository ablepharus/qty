#ifndef YOUTUBESEARCHER_H
#define YOUTUBESEARCHER_H

#include <QObject>
#include <QSettings>
#include <QProcess>
#include <QLoggingCategory>
#include <QThread>
Q_DECLARE_LOGGING_CATEGORY(youtube)

//class YtSearch : QObject
//{
//    Q_OBJECT
//public:
//    //explicit YtSearch(QString query, int count);
//public slots:
//    void query(QString query, int count);
//signals:
//    void queryResult(QByteArray jsonArr);
//};


class YoutubeService
{

};
#include <QFuture>
#include <QFutureWatcher>

// A class that invokes youtube-dl and passes results
class YoutubeDl : public QObject
{
    Q_OBJECT
public:
    explicit YoutubeDl(QObject *parent = nullptr);

    QByteArray query(QString query, int max=10);

    void getPythonVersion();
    void getYoutubeDlVersion();
protected:
    QByteArray _run(QString program, QStringList parameter);
    QByteArray run_python(QStringList parameter);
    QByteArray run_python_code(QString code);

    std::function<QByteArray(QStringList)> run_ytdl;

    QString m_python_interpreter{QSettings{}.value(
        "python-interpreter",
        "/home/ablepharus/.std/bin/python").toString()};
    bool m_explicit_python{QSettings{}.value(
        "explicit-python-interpreter",
        true).toBool()};
    QString m_ytdl{QSettings{}.value(
        "ytdl-path",
        "/home/ablepharus/.std/bin/youtube-dl").toString()};

    QProcess m_process;
    QString py_version;
    QString ytdl_version;
signals:

};

#endif // YOUTUBESEARCHER_H
