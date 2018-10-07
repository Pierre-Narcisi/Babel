#include <cstring>
#include "call.h"
#include <QCryptographicHash>

call::call(quint32 ip): _t(this)
{
   _ip = ip;
    QThread* thread = new QThread;
    this->moveToThread(thread);
    connect(this, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(thread, SIGNAL(started()), this, SLOT(process()));
    connect(this, SIGNAL(finished()), thread, SLOT(quit()));
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void call::process()
{
	_udpWrapper = new UdpWrapper();
	connect(_udpWrapper, &UdpWrapper::packetReceive, 
			this, &call::onPacketReceived);
	SoundWrapper &soundWrapper = Singletons::getSoundWrapper();

	connect(*soundWrapper, &SoundWrapper::readySend, [this, &soundWrapper] (char *buffer) {
        auto	p = babel::protocol::VoicePacket::create(8192);

        std::memmove(p->data, buffer, 8192);
        _udpWrapper->sendData(*p, _ip);
        delete buffer;
    });
    _t.start(1);
}

void call::onPacketReceived(std::shared_ptr<babel::protocol::VoicePacket> pack) {
	auto 		&sw = Singletons::getSoundWrapper();
	CompData	d;
    auto        *curNode = reinterpret_cast<BufferNode*>(pack.data);
    std::queue<CompData> toPlay;

    while (curNode->length) {
        toPlay.emplace();
        auto &cd = toPlay.back();

        cd.length = curNode->length;
        cd.assign(curNode.data, curNode.data + curNode->length);
        curNode = reinterpret_cast<BufferNode*>(
            reinterpret_cast<void*>(curNode) + cd.length + sizeof(*curNode));

    }
	sw.setPlayData(toPlay);
}