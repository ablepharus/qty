#include "youtubesearcher.h"
#include <QDebug>
#include <QFutureWatcher>
Q_LOGGING_CATEGORY(youtube, "youtube")


class PythonSubprocessError
{
    PythonSubprocessError(QString errorString)
        :errorString(errorString) {}
    QString errorString;
};


QByteArray YoutubeDl::query(QString query, int max)
{
    return QByteArray(run_ytdl(QStringList{}
                    << "-J" << "--no-warnings" // << "--flat-playlist"
                    << QString{"ytsearch%1://%2"}.arg(max).arg(query)));
}

YoutubeDl::YoutubeDl(QObject *parent) : QObject(parent)
{
    try {
            try {
                py_version = run_python_code(
                            "import sys\nprint(sys.__version__)");
            } catch (PythonSubprocessError e) {
                qDebug() << "Python not invokable";
                throw std::move(e);
            }
            try {
                ytdl_version = run_python_code(
                            "import youtube_dl\nprint(youtube_dl.__version__)");
                run_ytdl = [this](QStringList p) {
                    return this->run_python(
                        (QStringList{} << "-m" << "youtube_dl" ) + p);};
            } catch (PythonSubprocessError e) {
                qDebug() << "Youtube DL not found";
                throw std::move(e);
            }

    } catch (PythonSubprocessError e) {
        try {
            ytdl_version = _run(m_ytdl, QStringList{} << "-v");
            run_ytdl = [this](QStringList p) {return this->_run(m_ytdl, p);};
        } catch (PythonSubprocessError e) {
            qDebug() << "Could not find a way to execut youtube-dl";
            throw std::move(e);
        }
    }

    qDebug() << "Python version: " << py_version
             << "youtube-dl version: " << ytdl_version;
}

QByteArray YoutubeDl::_run(QString program, QStringList parameter)
{
    QProcess m_process{};
    //if(m_process.state() == QProcess::Running)
    //    m_process.kill();

    m_process.start(program, parameter);

    if(!m_process.waitForFinished())
    {
        qDebug() << m_process.errorString();
    }

    return m_process.readAllStandardOutput();
}

QByteArray YoutubeDl::run_python(QStringList parameter)
{
    return _run(m_python_interpreter, parameter);
}

QByteArray YoutubeDl::run_python_code(QString code)
{
    return run_python(QStringList{} << "-c" << code);
}
