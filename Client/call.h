#include <QUdpSocket>
#include <QKeyEvent>
#include <QAction>
#include <QObject>
#include <QNetworkDatagram>
#include <QDebug>
#include <QTimer>
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
        call(quint32);
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
        UdpWrapper	*_udpWrapper;
	quint32		_ip;
	QTimer		_t;
    public:
};

#endif // CALL_H
