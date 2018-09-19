#include <QDir>
#include <QFileInfo>
#include <QTimer>
#include <tuple>
#include "frienditem.h"
#include "resoucesdownloader.h"
#include "singletons.h"

ResoucesDownloader::ResoucesDownloader(QObject *parent, json::Entity &&sheet) :
    QObject(parent),
    _t(this),
    _m(Singletons::getManager()),
    _p(reinterpret_cast<FriendItem*>(parent))
{
    _initLists(_toDl, sheet["toDownload"]);
}

ResoucesDownloader::~ResoucesDownloader()
{
    for (QNetworkReply *r : _rList) {
        r->abort();
        r->deleteLater();
    }
}

ResoucesDownloader*
ResoucesDownloader::downloadResources(QObject *parent, const json::Entity &sheet)
{
    auto drsc = new ResoucesDownloader(parent, json::Entity(sheet));

    return drsc;
}

void ResoucesDownloader::_initLists(std::vector<ResoucesDownloader::rscSheets> &vec,
                                    json::Entity &jsonList)
{
    if (!jsonList.isArray())
        return;
    for (json::Entity &obj : jsonList.getData<json::Array>().get()) {
        _fileNumber++;
        vec.emplace_back(obj["url"].to<std::string>(), obj["fileName"].to<std::string>());
    }
}

void ResoucesDownloader::_startFileDownload(ResoucesDownloader::rscSheets &elem)
{
    QFileInfo       finfo(elem.filePath);
    QNetworkReply   *r = _m->get(
                QNetworkRequest(QUrl(elem.url)));

    if (finfo.absoluteDir().exists() == false)
        finfo.absoluteDir().mkpath(finfo.absoluteDir().path());
    _rList.push_back(r);
    auto    it = _rList.end();
    it--;
    connect(r, &QNetworkReply::finished, [this, elem, it] () {
        if ((*it)->error() == QNetworkReply::NoError) {
            QFile   fstm(elem.filePath);

            if (fstm.open(QFile::WriteOnly)) {
                fstm.write((*it)->readAll());
            }
            (*it)->deleteLater();
            _mtx.lock();
            _rList.erase(it);
            _fileCompleted++;
            if (_fileCompleted == _fileNumber) {
                _speedList.clear();
                emit onComplete();
                _t.stop();
            }
            _mtx.unlock();
        } else {
            _mtx.lock();
            (*it)->deleteLater();
            _rList.erase(it);
            emit onError();
            _t.stop();
            _mtx.unlock();
        }
    });
    r->setProperty("first", true);
    r->setProperty("last", (qint64) 0);
    connect(r, &QNetworkReply::downloadProgress, [this, r] (qint64 rec, qint64 total) {
        bool     first = r->property("first").toBool();
        qint64   last = r->property("last").toULongLong();

        if (r->error() == QNetworkReply::NoError) {
            _mtx.lock();
            if (first) {
                _bytesTotal += total;
                r->setProperty("first", false);
             }
            _bytesDownloaded += rec - last;
            r->setProperty("last", rec);
            emit onProgress(_bytesDownloaded * 100 / _bytesTotal, _speed);
            _mtx.unlock();
        }
    });
}

QString	ResoucesDownloader::prettySize(qint64 size)
    {
        double		res = size;
        static const std::vector<std::tuple<QString, double>> tab = {
            std::make_tuple("o", 0.0),
            std::make_tuple("ko", 1000.0),
            std::make_tuple("mo", 1000000.0),
            std::make_tuple("go", 1000000000.0),
            std::make_tuple("", -1.0)
        };

        for (int i = 0; std::get<1>(tab[i]) != -1.0; i++) {
            if ((std::get<1>(tab[i + 1]) == -1.0) ||
                (res > std::get<1>(tab[i]) && std::get<1>(tab[i + 1]) > res))
                return (QString::number(res / std::get<1>(tab[i]), 10, 2) + " " + std::get<0>(tab[i]));
        }
        return ("");
    }


void    ResoucesDownloader::start(void)
{
    for (auto &elem : _toDl) {
        _startFileDownload(elem);
    }
    connect(&_t, &QTimer::timeout, [this] () {
        qint64                      speed = 0;

        if (_speedList.size() > 15) {
            _speedList.pop_front();
        }
        _speedList.push_back((_bytesDownloaded - _last) * 4);
        for (auto s : _speedList) {
            speed += s;
        }
        speed /= _speedList.size();
        _speed = speed;
        _last = _bytesDownloaded;
    });
    _t.start(250);
}
