#ifndef SINGLETONS_H
#define SINGLETONS_H

#include <QNetworkAccessManager>
#include <QThreadPool>

class Singletons
{
public:
    static QNetworkAccessManager*
                    getManager(void);
    static QThreadPool*
                    getThreadPool(void);
private:
    Singletons() = default;
};

#endif // SINGLETONS_H
