#include "udpwrapper.h"

UdpWrapper::UdpWrapper(QObject *parent) : QObject(parent)
{
    _udpSocket = new QUdpSocket(this);
    _udpSocket->bind(QHostAddress::LocalHost, 6666);
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
    QByteArray data = datagram.data();
    std::string str = data.toStdString();

}

void        UdpWrapper::sendData(QString data)
{
    qint64  size = data.size();
    QHostAddress addr(QHostAddress::LocalHost);
    _udpSocket->writeDatagram(data.toStdString().c_str(), size, addr, 6666);
}
