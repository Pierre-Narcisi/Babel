#include <QStandardPaths>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include "settings.h"

#include <iostream>

Settings::Settings():
    QJsonObject(),
    _dataPath(QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation)[0]),
    _settingFilePath(_dataPath + "/.settings.json")
{
    QFileInfo   settingFileInfo(_settingFilePath);

    if (settingFileInfo.absoluteDir().exists() == false)
        settingFileInfo.absoluteDir().mkpath(settingFileInfo.absolutePath());

    QFile file(_settingFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         return;
    _doc = QJsonDocument::fromJson(file.readAll());
    (*dynamic_cast<QJsonObject*>(this)) = _doc.object();
}

Settings::~Settings() {
    save();
}

void    Settings::save(void) {
    QFile file(_settingFilePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
         return;
    _doc.setObject(*dynamic_cast<QJsonObject*>(this));
    file.write(_doc.toJson());
}
