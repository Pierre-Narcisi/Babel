#include "call.h"

call::call()
{
}

void        call::initsocket()
{
    _udpSocket = new QUdpSocket(this);
    connect(_udpSocket, SIGNAL(readyRead()), this, SLOT(readData()));
}

void        call::readData()
{
    while (_udpSocket->hasPendingDatagrams()) {
         QNetworkDatagram datagram = _udpSocket->receiveDatagram();
         processData(datagram);
    }
}

void        call::processData(QNetworkDatagram datagram)
{
    QByteArray data;

    data = datagram.data();
    qDebug() << data;
    sendData();
}

void        call::sendData()
{
    QString data = "hello world!";
    qint64  size = data.size();
    QHostAddress addr("localhost");
    quint16 port = 0;

    _udpSocket->writeDatagram(data.toStdString().c_str(), size, addr, port);
}
