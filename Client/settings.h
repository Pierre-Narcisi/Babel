#ifndef SETTINGS_H
#define SETTINGS_H

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class Settings: public QJsonObject
{
public:
    Settings();
    ~Settings();

    void save(void);
private:
    QString _dataPath;
    QString _settingFilePath;

    QJsonDocument _doc;
};

#endif // SETTINGS_H
