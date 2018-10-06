#include <QStringList>
#include "version.h"

#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)


inline Version &Version::_get()
{
    static Version  vers;

    return vers;
}

QString Version::toString()
{
    static Version &obj = _get();

    return obj._version_str;
}

int Version::getVersion()
{
    static Version &obj = _get();

    return obj._version;
}

int Version::getRevision()
{
    static Version &obj = _get();

    return obj._revision;
}

int Version::getPatch()
{
    static Version &obj = _get();

    return obj._patch;
}

Version::Version()
{
#ifdef  VERSION
    _version_str = QString(TO_STRING(VERSION));
#else
    _version_str = "0.1.0";
#endif
    QStringList splited = _version_str.split(".");

    if (splited.size() > 0)
        _version = splited[0].toInt();
    if (splited.size() > 1)
        _revision = splited[1].toInt();
    if (splited.size() > 2)
        _patch = splited[2].toInt();
}


