#include "call.h"

call::call()
{
    _i = 0;
}

void        call::readData()
{
    while (_udpSocket->hasPendingDatagrams()) {
         QNetworkDatagram datagram = _udpSocket->receiveDatagram();
         processData(datagram);
    }
}

void        call::initsocket(quint16 port)
{
    _udpSocket = new QUdpSocket(this);
    _udpSocket->bind(QHostAddress::LocalHost, port);
    connect(_udpSocket, SIGNAL(readyRead()), this, SLOT(readData()));
}

void        call::processData(QNetworkDatagram datagram)
{
    QByteArray data;

    data = datagram.data();
    qDebug() << data;
}

QUdpSocket  *call::getSocket()
{
    return _udpSocket;
}

quint16     call::getPort()
{
    return _port;
}

void        call::setPort(quint16 port)
{
    _port = port;
}

void        call::sendData(quint16 port)
{
    setPort(port);
    QThread* thread = new QThread;
    MyObject* myObject = new MyObject(port, _udpSocket);
    myObject->moveToThread(thread);
    connect(myObject, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(thread, SIGNAL(started()), myObject, SLOT(process()));
    connect(myObject, SIGNAL(finished()), thread, SLOT(quit()));
    connect(myObject, SIGNAL(finished()), myObject, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void MyObject::process()
{
    int i = 0;
    while (i < 10000000) {
        QString data = QString::number(i);
        qint64  size = data.size();
        QHostAddress addr(QHostAddress::LocalHost);
        _udpSocket->writeDatagram(data.toStdString().c_str(), size, addr, _port);
        i++;
    }
}

MyObject::MyObject(quint16 port, QUdpSocket *udpSocket)
{
    _port = port;
    _udpSocket = udpSocket;
}

MyObject::~MyObject()
{

}
