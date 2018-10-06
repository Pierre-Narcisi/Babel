#include "soundwrapper.h"

SoundWrapper::SoundWrapper(QObject *parent) : QObject(parent), _paWrapper()
{
    _paWrapper.startRecord();
    _paWrapper.startPlay();
}

PaWrapper &SoundWrapper::getPa()
{
    return _paWrapper;
}
