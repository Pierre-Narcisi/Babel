#ifndef HASHCHECKER_H
#define HASHCHECKER_H

#include <QList>
#include <QRunnable>
#include <QThread>
#include <functional>
#include "Json/Entity.hpp"

#ifdef TARGET_UNIX
 #define TARGETSTR "linux"
#elif TARGET_WINDOWS
 #define TARGETSTR "windows"
#elif TARGET_MACOS
 #define TARGETSTR "macos"
#endif

class HashChecker : public QObject, private QRunnable
{
    Q_OBJECT
public:
    static HashChecker *
    needUpdate(json::Entity const &sheet, QObject *parent = nullptr);
    static void
    createGameHash(json::Entity &sheet);

    void    abort(void);
    void    run();
signals:
    void    onComplete(json::Entity data);
private:
    static inline json::Entity
    _getFor(QString &&absPath, json::Entity &datas, QString &&path);

    explicit HashChecker(QObject *parent, json::Entity const &sheet);

    json::Entity    _sheet;
    bool            _aborted = false;
};

#endif // HASHCHECKER_H
