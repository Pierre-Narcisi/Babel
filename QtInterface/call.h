#include <QUdpSocket>
#include <QKeyEvent>
#include <QAction>
#include <QObject>
#include <QNetworkDatagram>
#include <QDebug>

#ifndef CALL_H
#define CALL_H


class call : public QObject
{
    Q_OBJECT
    public:
        call();
    private:
        QUdpSocket *_udpSocket;
        uint16_t _servport;
    public:
        void        processData(QNetworkDatagram datagram);
        void        initsocket();
        void        readData();
        void        sendData();
};

#endif // CALL_H
