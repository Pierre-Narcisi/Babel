
#include "soundwrapper.h"

SoundWrapper::SoundWrapper(QObject *parent) : QObject(parent), _paWrapper()
{
    _paWrapper.startRecord();
    _paWrapper.startPlay();

    auto t = new std::thread([this] {
        char    voidd[235] = {0};
        while (true) {
            _m.lock();
            _paWrapper.play(_d);
            _d.length = 235;
            _d.data.assign(voidd, (char*) voidd + 235);
            _m.unlock();
        }
    });
}

PaWrapper &SoundWrapper::getPa()
{
    return _paWrapper;
}
