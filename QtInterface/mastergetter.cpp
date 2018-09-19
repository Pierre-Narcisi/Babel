#include <QNetworkReply>
#include <iostream>
#include <QObject>
#include <QFileInfo>
#include <QDir>
#include <mutex>
#include "cache.h"
#include "singletons.h"
#include "mastergetter.h"
#include "Json/Parser.hpp"

MasterGetter::MasterGetter():
    _manager(Singletons::getManager()) {}

MasterGetter::~MasterGetter()
{

}

void MasterGetter::setMaster(const QString &str)
{
    _masterPos = _getCurrentPos(str).toStdString();
    _masterUrl = str;
}

const QString &MasterGetter::getMaster() const
{
    return _masterUrl;
}

void MasterGetter::loadMaster(std::function<void(json::Entity const &)> const &onLoaded,
                              std::function<void()> const &onError)
{
    if (_masterPos.empty())
        return;
    QNetworkReply   *reply = _manager->get(
                QNetworkRequest(QUrl(_masterUrl)));
    QObject::connect(reply, &QNetworkReply::finished, [this, reply, onLoaded, onError] () {
        if (reply) {
            if (reply->error() == QNetworkReply::NoError) {
                auto        datas = reply->readAll();
                Cache::saveToCache(_masterUrl, datas);
                QString myCustomData(datas);
                _data = json::Parser::fromString(myCustomData.toStdString());
                _loadSheets(onLoaded, _masterPos);
            } else {
                QByteArray data = Cache::getCachedData(_masterUrl);
                if (data.isEmpty() == false) {
                    _data = json::Parser::fromString(data.toStdString());
                    _loadSheets(onLoaded, _masterPos);
                } else {
                    onError();
                }
            }
            reply->deleteLater();
        }
    });
}

const json::Entity &MasterGetter::getData(void) const
{
    return _data;
}

QString MasterGetter::_getCurrentPos(const QString &url)
{
    QFileInfo   fi(url);
    QDir        fdir(fi.dir());

    return fdir.path();
}

void MasterGetter::_filterString(json::Entity &str, std::string const &current)
{
    const std::unordered_map<std::string, const std::string> command_map {
        {"currentLocation", current},
        {"masterLocation", _masterPos}
    };
    std::string         &s = const_cast<std::string&>(str.getData<json::String>().get());
    ssize_t             start = -1;
    bool                lock = false;
    std::size_t         i = 0;

    for (std::size_t j = 0; j < s.length(); ++j) {
        char c = s[j];
        if (lock) {
            if (c == '}') {
                std::string key = s.substr(start + 2, i - start - 2);
                auto        it = command_map.find(key);

                lock = false;
                if (it != command_map.end())
                   s.replace(start, i - start + 1, it->second);
            }
        } else {
            if (c == '{' && start != -1) {
                lock = true;
            } else if (start != -1) {
                start = -1;
            }
            if (c == '$')
                start = i;
        }
        ++i;
    }
}

void MasterGetter::_resolveJson(json::Entity &data, std::string const &current)
{
    if (data.isArray()) {
        auto    &ary = data.getData<json::Array>().get();

        for (auto &s : ary) {
            _resolveJson(s, current);
        }
    } else if (data.isObject()) {
        auto    &obj = data.getData<json::Object>().get();

        for (auto &s : obj) {
            _resolveJson(s.second, current);
        }
    } else if (data.isString()) {
        _filterString(data, current);
    }
}

void MasterGetter::_loadSheets(std::function<void(json::Entity const &)> const &onLoaded,
                               std::string const &current)
{
    std::mutex  *cpLock = new std::mutex();
    int         *cmpt = new int(0);
    auto        &games = _data["games"].getData<json::Array>().get();

    _resolveJson(_data, current);
    for (auto &gameUrl : games) {
        QString         strUrl = QString::fromStdString(gameUrl.getData<json::String>().get());
        QNetworkReply   *reply = _manager->get(QNetworkRequest(QUrl(strUrl)));
        auto            cur = _getCurrentPos(strUrl).toStdString();

        cpLock->lock();
        (*cmpt)++;
        cpLock->unlock();
        QObject::connect(reply, &QNetworkReply::finished,
        [this, cpLock, cmpt, &gameUrl, reply, cur, onLoaded, strUrl] () {
            auto onDataLoaded = [&] (std::string &&sheet) {
                try {
                    gameUrl = json::Parser::fromString(sheet);
                    gameUrl["from"] = strUrl.toStdString();
                } catch (std::exception &) {
                    std::cout << "Error: invalid master sheet" << std::endl;
                }
                _resolveJson(gameUrl, cur);
                if (*cmpt == 0) {
                    onLoaded(_data);
                }
            };

            cpLock->lock();
            (*cmpt)--;
            if (reply) {
                if (reply->error() == QNetworkReply::NoError) {
                    QByteArray  datas = reply->readAll();

                    Cache::saveToCache(strUrl, datas);
                    onDataLoaded(datas.toStdString());
                } else {
                    QByteArray data = Cache::getCachedData(strUrl);
                    if (data.isEmpty() == false) {
                        onDataLoaded(data.toStdString());
                    }
                }
                reply->deleteLater();
            }
            cpLock->unlock();
        });
    }
}
