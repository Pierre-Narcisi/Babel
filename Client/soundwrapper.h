#ifndef SOUNDWRAPPER_H
#define SOUNDWRAPPER_H

#include <thread>
#include <mutex>
#include <QObject>
#include <queue>
#include "PaWrapper/PaWrapper.hpp"

#ifdef _WIN32
# pragma pack(push,1)
#endif

#define BUFFER_SIZE 8196

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
signals:
    void    readySend(char *buffer);
private:
    PaWrapper               _paWrapper;
    std::queue<CompData>    _playD;
    std::mutex              _playM;
signals:

public slots:
};

#endif // SOUNDWRAPPER_H
