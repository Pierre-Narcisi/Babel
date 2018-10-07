#include <QHostAddress>
#include <cstring>
#include <memory>
#include "udpwrapper.h"

UdpWrapper::UdpWrapper(QObject *parent) : QObject(parent)
{
    _udpSocket = new QUdpSocket(this);
    _udpSocket->bind(QHostAddress::Any, 6666);
    connect(_udpSocket, SIGNAL(readyRead()), this, SLOT(readData()));
}

void        UdpWrapper::readData()
{
    while (_udpSocket->hasPendingDatagrams()) {
         QNetworkDatagram datagram = _udpSocket->receiveDatagram();
         processData(datagram);
    }
}

void        UdpWrapper::processData(QNetworkDatagram datagram)
{
	QByteArray	data = datagram.data();
	char 		*rawdata = new char[data.size()];
	std::memmove(rawdata, data.data(), data.size());

	auto	packet = std::shared_ptr<babel::protocol::VoicePacket>
				(reinterpret_cast<babel::protocol::VoicePacket*>(rawdata));
	if (packet->type == babel::protocol::Packet::Type::VoicePacket) {
		emit packetReceive(packet);
	} else {

	}
}

void        UdpWrapper::sendData(babel::protocol::VoicePacket &packet, quint32 ip)
{
    QHostAddress addr(ip);
    _udpSocket->writeDatagram(reinterpret_cast<char*>(&packet), packet.packetSize, addr, 6666);
}
