#ifndef RESOUCESDOWNLOADER_H
#define RESOUCESDOWNLOADER_H

#include <vector>
#include <list>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <mutex>
#include "Json/Entity.hpp"

class FriendItem;

class ResoucesDownloader : public QObject
{
    Q_OBJECT
private:
    struct  rscSheets;

public:
    ~ResoucesDownloader();
    static ResoucesDownloader*
    downloadResources(QObject *parent, json::Entity const &sheet);

    void            start(void);
    static QString	prettySize(qint64 size);
private:
    explicit ResoucesDownloader(QObject *parent, json::Entity &&sheet);

    void    _initLists(std::vector<ResoucesDownloader::rscSheets> &vec,
                       json::Entity &jsonList);
    void    _startFileDownload(rscSheets &);
signals:
    void    onComplete();
    void    onError();
    void    onProgress(int, qint64);

private:
    struct  rscSheets {
        rscSheets(std::string const &_url, std::string const &_fPath):
            url(QString::fromStdString(_url)),
            filePath(QString::fromStdString(_fPath)) {}
        QString url;
        QString filePath;
    };

    std::mutex                  _mtx;
    std::vector<rscSheets>      _toDl;
    std::list<QNetworkReply*>   _rList;
    std::list<qint64>           _speedList;
    qint64                      _last = 0;
    qint64                      _bytesDownloaded = 0;
    qint64                      _bytesTotal = 0;
    qint64                      _speed = 0;
    int                         _fileNumber = 0;
    int                         _fileCompleted = 0;
    QTimer                      _t;
    QNetworkAccessManager       *_m;
    FriendItem                    *_p;

};

#endif // RESOUCESDOWNLOADER_H
