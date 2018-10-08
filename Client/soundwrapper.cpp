
#include <chrono>
#include "soundwrapper.h"

SoundWrapper::SoundWrapper(QObject *parent) : QObject(parent), _paWrapper()
{
    _t = std::unique_ptr<std::thread>(new std::thread([this] {
        char                    voidd[235] = {0};
        char                    buf[BUFFER_SIZE] = {0};
        std::uint32_t           offset = 0;
        CompData                ah;

        ah.length = 235;
        ah.data.assign(voidd, (char*) voidd + 235);
        while (!_end) {
            if (_count == 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                continue;
            }
            _playM.lock();
            if (_startNow) {
                _paWrapper.startRecord();
                _paWrapper.startPlay();
                _startNow = false;
            }
            _paWrapper.record();
		    auto d = _paWrapper.getData();
            if (offset + d.length + sizeof(BufferNode) >= sizeof(buf)) {
                char *copy = (char*) ::operator new(sizeof(buf));

                std::memmove(copy, buf, sizeof(buf));
                reinterpret_cast<std::uint32_t*>(copy + offset)[0] = 0;
                if (readySend != nullptr)
                    readySend(copy);
                offset = 0;
            }
            reinterpret_cast<BufferNode*>(buf + offset)->length = d.length;
            std::memmove(
                reinterpret_cast<BufferNode*>(buf + offset)->data,
                reinterpret_cast<char*>(d.data.data()), d.length);
            offset += d.length + sizeof(BufferNode);
            if (_playD.size()) {
                _paWrapper.play(_playD.front());
                _playD.pop();
            } else {
                _paWrapper.play(ah);
            }
            _playM.unlock();
        }
    }));
}

void    SoundWrapper::registerCall(void) {
    _count++;
    _startNow = true;
}

void    SoundWrapper::unRegisterCall(void) {
    _playM.lock();
    _count--;
    if (_count <= 0) {
        _paWrapper.stopRecord();
        _paWrapper.stopPlay();
    }
    _playM.unlock();
}

void    SoundWrapper::stop(void) {
    _end = true;
    _t->join();
}

PaWrapper &SoundWrapper::getPa()
{
    return _paWrapper;
}
