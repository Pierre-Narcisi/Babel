#ifndef SOUNDWRAPPER_H
#define SOUNDWRAPPER_H

#include <thread>
#include <mutex>
#include <QObject>
#include "PaWrapper/PaWrapper.hpp"

class SoundWrapper : public QObject
{
    Q_OBJECT
public:
    explicit SoundWrapper(QObject *parent = nullptr);

    void        setData(CompData const &d) {
        _m.lock();
        _d = d;
        _m.unlock();
    }
    PaWrapper   &getPa();
private:
    PaWrapper   _paWrapper;
    CompData    _d;
    std::mutex  _m;
signals:

public slots:
};

#endif // SOUNDWRAPPER_H
