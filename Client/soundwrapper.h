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

    void        setPlayData(CompData const &d) {
        _playM.lock();
        _playD = d;
        _playM.unlock();
    }
    CompData       getRecordData() {
        return _recordD;
    }
    PaWrapper   &getPa();
private:
    PaWrapper   _paWrapper;
    CompData    _playD;
    std::mutex  _playM;
    CompData    _recordD;
    std::mutex  _recordM;
signals:

public slots:
};

#endif // SOUNDWRAPPER_H
