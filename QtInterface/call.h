#include <QUdpSocket>
#include <QKeyEvent>
#include <QAction>
#include <QObject>
#include <QNetworkDatagram>
#include <QDebug>
#include <QThread>
#include "udpwrapper.h"
#include "singletons.h"
#include "soundwrapper.h"

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

    public:
};

class MyObject: public QObject
{
    Q_OBJECT
    public:
         MyObject();
         ~MyObject();
    public slots:
        void process();
    signals:
        void finished();
        void error(QString err);
    private:
        UdpWrapper *_udpWrapper;
};

#endif // CALL_H
