
#include "soundwrapper.h"

SoundWrapper::SoundWrapper(QObject *parent) : QObject(parent), _paWrapper()
{
    _paWrapper.startRecord();
    _paWrapper.startPlay();
    new std::thread([this] {
        char                    voidd[235] = {0};
        char                    buf[8192] = {0};
        std::uint32_t           offset = 0;
        _playD.emplace();
        _playD.front().length = 235;
        _playD.front().data.assign(voidd, (char*) voidd + 235);
        while (true) {
            _playM.lock();
            _paWrapper.record();
		    auto d = _paWrapper.getData();
            if (offset + d.length + sizeof(BufferNode) >= sizeof(buf)) {
                char *copy = (char*) ::operator new(sizeof(buf));

                std::memmove(copy, buf, sizeof(buf));
                reinterpret_cast<std::uint32_t*>(copy + offset)[0] = 0;
                emit readySend(copy);
                offset = 0;
            }
            reinterpret_cast<BufferNode*>(buf + offset)->length = d.length;
            std::memmove(
                &(reinterpret_cast<BufferNode*>(buf + offset)->data),
                reinterpret_cast<char*>(&d), d.length);
            offset += d.length + sizeof(BufferNode);
            _paWrapper.play(_playD.front());
            if (_playD.size() <= 1)
                _playD.pop();
            _playD.front().length = 235;
            _playD.front().data.assign(voidd, (char*) voidd + 235);
            _playM.unlock();
        }
    });
}

PaWrapper &SoundWrapper::getPa()
{
    return _paWrapper;
}
