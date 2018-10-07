#ifndef UDPWRAPPER_H
#define UDPWRAPPER_H

#include <QUdpSocket>
#include <QObject>
#include <QNetworkDatagram>
#include <memory>
#include "Protocol/Protocol.h"

class UdpWrapper : public QObject
{
    Q_OBJECT
public:
    explicit    UdpWrapper(QObject *parent = nullptr);
    void        processData(QNetworkDatagram datagram);
    void        sendData(babel::protocol::VoicePacket &packet, quint32 ip);

signals:
	void	packetReceive(std::shared_ptr<babel::protocol::VoicePacket> pack);

public slots:
    void readData();
private:
    QUdpSocket *_udpSocket;
};

#endif // UDPWRAPPER_H
