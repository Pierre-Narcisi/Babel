#include <QUdpSocket>
#include <QKeyEvent>
#include <QAction>
#include <QObject>
#include <QNetworkDatagram>
#include <QDebug>
#include <QThread>

#ifndef CALL_H
#define CALL_H


class call : public QObject
{
    Q_OBJECT
    public:
        call();
    private:
        QUdpSocket *_udpSocket;
        quint16 _port;
        int _i;
    private slots:
        void        readData();
    public:
        void        processData(QNetworkDatagram datagram);
        QUdpSocket  *getSocket();
        quint16     getPort();
        void        setPort(quint16 port);
        void        initsocket(quint16 port);
        void        sendData(quint16 port);
};

class MyObject: public QObject
{
    Q_OBJECT
    public:
         MyObject(quint16 port, QUdpSocket *udpSocket);
         ~MyObject();
    public slots:
        void process();
    signals:
        void finished();
        void error(QString err);
    private:
        quint16 _port;
        QUdpSocket *_udpSocket;
};

#endif // CALL_H
