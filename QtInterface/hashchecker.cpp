#include <QUrl>
#include <QDir>
#include <QFileInfo>
#include "cache.h"
#include "singletons.h"
#include "hashchecker.h"

#include <iostream>

#define MAKEURLRESULT(url, filePath)  json::makeObject { \
    {"url", url}, \
    {"fileName", (filePath).toStdString()} \
});

inline json::Entity
HashChecker::_getFor(QString &&absPath, json::Entity &datas, QString &&path)
{
    json::Entity    arrResult(json::Entity::ARR);
    if (datas.isArray() == false)
        return (arrResult);

    QString    currentDir(absPath + '/' + path);
    for (auto &libsheet : datas.getData<json::Array>().get()) {
        QFileInfo   urlFile(QString::fromStdString(libsheet["url"].to<std::string>()));
        QString     fileName(currentDir +
                             (libsheet["sub-dir"].isString()
                               ? QString::fromStdString(libsheet["sub-dir"].to<std::string>()) + "/"
                               : "") + urlFile.fileName());
        QFile       f(fileName);

        if (f.exists()) {
            f.open(QFile::ReadOnly);
            QByteArray  hash(QCryptographicHash::hash(f.readAll(), QCryptographicHash::Sha256).toHex());
            if (libsheet["sha256"].to<std::string>() != hash.toStdString())
                arrResult.push(
                            MAKEURLRESULT(libsheet["url"], fileName);
        } else {
            arrResult.push(
                        MAKEURLRESULT(libsheet["url"], fileName);
        }
    }
    return arrResult;
}

HashChecker::HashChecker(QObject *parent, json::Entity const &sheet) :
    QObject(parent),
    _sheet(sheet) {}

HashChecker *HashChecker::needUpdate(json::Entity const &sheet, QObject *parent)
{
    QThreadPool     *tp = Singletons::getThreadPool();
    HashChecker     *hc = new HashChecker(parent, sheet);

    hc->setAutoDelete(false);
    tp->start(hc);
    return (hc);
}


void HashChecker::abort()
{
    this->_aborted = true;
}

void HashChecker::run()
{
    createGameHash(_sheet);
    QString         dirName = QString::fromStdString(_sheet["hashName"].to<std::string>());
    QDir            dir(Cache::getDataDirectory() + '/' + dirName);
    json::Entity    toDownload(json::makeObject {
        {"isNewInstall", false},
        {"needDownload", false},
        {"toDownload", json::Entity::ARR},
        {"path", dir.absolutePath().toStdString()}
    });

    if (dir.exists() == false) {
        toDownload["isNewInstall"] = true;
    }
    if (_sheet["entry"].isObject() && _sheet["entry"][TARGETSTR].isString())
        toDownload["entry"] = _sheet["entry"][TARGETSTR];
    if (_sheet["binary"].isObject() && _sheet["binary"][TARGETSTR].isArray())
        toDownload["toDownload"] = _getFor(dir.absolutePath(), _sheet["binary"][TARGETSTR], "");
    if (_sheet["assets"].isArray())
        toDownload["toDownload"].merge(_getFor(dir.absolutePath(), _sheet["assets"], "assets/"));
    if (toDownload["toDownload"].getData<json::Array>().get().empty() == false) {
        toDownload["needDownload"] = true;
    }
    if (!_aborted) {
        emit onComplete(toDownload);
    }
    deleteLater();
}
