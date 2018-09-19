#ifndef VERSION_H
#define VERSION_H

#include <QString>

class Version
{
public:
    static QString  toString();
    static int      getVersion();
    static int      getRevision();
    static int      getPatch();

    QString _version_str;
    int     _version;
    int     _revision;
    int     _patch;
private:
    explicit Version();

    static inline Version  &_get(void);
};

#endif // VERSION_H
