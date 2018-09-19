#ifndef MASTERGETTER_H
#define MASTERGETTER_H

#include <QString>
#include <string>
#include <functional>
#include <QNetworkAccessManager>
#include "Json/Entity.hpp"

class MasterGetter
{
public:
    MasterGetter();
    ~MasterGetter();

    void            setMaster(QString const &str);
    const QString   &getMaster(void) const;
    void            loadMaster(std::function<void(json::Entity const &)> const &loaded,
                               std::function<void()> const &onError);
    const json::Entity&
                    getData(void) const;
private:

    QString _getCurrentPos(QString const &url);
    void    _filterString(json::Entity &str, std::string const &current);
    void    _resolveJson(json::Entity &data, std::string const &current);
    void    _loadSheets(std::function<void(json::Entity const &)> const &loaded,
                        std::string const &current);

    json::Entity            _data;
    QString                 _masterUrl;
    std::string             _masterPos;
    QNetworkAccessManager   *_manager;
};

#endif // MASTERGETTER_H
