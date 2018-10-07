#include <cstring>
#include "call.h"

call::call()
{
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
	SoundWrapper &soundWrapper = Singletons::getSoundWrapper();
	soundWrapper.getPa().startRecord();
	soundWrapper.getPa().startPlay();
	while (true) {
		std::cout << "TEST TEST TEST" << std::endl;
		soundWrapper.getPa().record();
		CompData d = soundWrapper.getPa().getData();
		soundWrapper.getPa().play(d);
		// auto	*p = new (d.data.size()) babel::protocol::VoicePacket;
		// std::memmove(p->data, d.data.data(), p->size);
		// p->length = d.length;
		// _udpWrapper->sendData(*p);
		// delete p;
	}
}

void call::onPacketReceived(std::shared_ptr<babel::protocol::VoicePacket> pack) {
	auto 		&sw = Singletons::getSoundWrapper().getPa();
	CompData	d;
	auto		*buffer = (unsigned char*) (pack->data);

	d.length = pack->length;
	d.data = std::vector<unsigned char>(buffer, buffer + pack->size);
	sw.play(d);
}