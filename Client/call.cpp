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
	
	connect(&_t, &QTimer::timeout, [this, &soundWrapper] {
		
	});
	_t.start(10);
}

void call::onPacketReceived(std::shared_ptr<babel::protocol::VoicePacket> pack) {
	auto 		&sw = Singletons::getSoundWrapper();
	CompData	d;
	auto		*buffer = (unsigned char*) (pack->data);

	d.length = pack->length;
	d.data = std::vector<unsigned char>(buffer, buffer + pack->size);
	std::cout << "to play = " << d.data.size() << std::endl;
		
	sw.setData(d);
}