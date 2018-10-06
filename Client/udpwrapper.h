#ifndef UDPWRAPPER_H
#define UDPWRAPPER_H

#include <QUdpSocket>
#include <QObject>
#include <QNetworkDatagram>

class UdpWrapper : public QObject
{
    Q_OBJECT
public:
    explicit    UdpWrapper(QObject *parent = nullptr);
    void        processData(QNetworkDatagram datagram);
    void        sendData(QString data);

signals:

public slots:
    void readData();
private:
    QUdpSocket *_udpSocket;
};

#endif // UDPWRAPPER_H
