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


class call : public QThread
{
    Q_OBJECT
    public:
        call();
    private:
        QUdpSocket *_udpSocket;
        quint16 _port;
        int _i;
    private slots:
	void process();
	void onPacketReceived(std::shared_ptr<babel::protocol::VoicePacket> pack);
    signals:
        void finished();
        void error(QString err);
    private:
        UdpWrapper *_udpWrapper;
    public:
};

#endif // CALL_H
