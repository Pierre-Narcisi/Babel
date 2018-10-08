#ifndef SOUNDWRAPPER_H
#define SOUNDWRAPPER_H

#include <thread>
#include <mutex>
#include <QObject>
#include <QUdpSocket>
#include <queue>
#include "PaWrapper/PaWrapper.hpp"

#ifdef _WIN32
# pragma pack(push,1)
#endif

#define BUFFER_SIZE 4096

struct BufferNode {
	std::uint32_t	length;
	unsigned char	data[];
} PACKET_ATTRIBUTE;

#ifdef _WIN32
# pragma pack(pop)
#endif

class SoundWrapper : public QObject
{
    Q_OBJECT
public:
    explicit SoundWrapper(QObject *parent = nullptr);

    void        setPlayData(std::queue<CompData> const &d) {
        _playM.lock();
        _playD = d;
        _playM.unlock();
    }
    PaWrapper   &getPa();

    std::function<void(char*)>
                            readySend;
    void    registerCall(void);
    void    unRegisterCall(void);

    void    stop(void);
signals:

private:
    PaWrapper               _paWrapper;
    std::queue<CompData>    _playD;
    std::mutex              _playM;
    int                     _count = 0;
    std::unique_ptr<std::thread>
                            _t;
    bool                    _end = false;
signals:

public slots:
};

#endif // SOUNDWRAPPER_H
