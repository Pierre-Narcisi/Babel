#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QString>
#include <QObject>
#include "Network/QtSocket.hpp"

class ServerConnection
{
public:
    ServerConnection(QObject *parent = nullptr);

    void setHost(QString const &host);
    void setPort(quint16 port);
    void setParent(QObject *parent);

    void connect(QString const &username, QString const &password, bool _register);

    int run(void);
private:
    QObject             *_parent;
    QString             _host;
    quint16             _port;
    nw::ATCPSocket      *_sock;
};

#endif // SERVERCONNECTION_H
