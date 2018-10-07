
#include "soundwrapper.h"

SoundWrapper::SoundWrapper(QObject *parent) : QObject(parent), _paWrapper()
{
    _paWrapper.startRecord();
    _paWrapper.startPlay();

    new std::thread([this] {
        char    voidd[235] = {0};
        while (true) {
            _playM.lock();
            _paWrapper.record();
		    _recordD = _paWrapper.getData();
            _paWrapper.play(_playD);
            _playD.length = 235;
            _playD.data.assign(voidd, (char*) voidd + 235);
            _playM.unlock();
        }
    });
}

PaWrapper &SoundWrapper::getPa()
{
    return _paWrapper;
}
