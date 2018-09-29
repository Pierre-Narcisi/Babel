#include "serverconnection.h"

ServerConnection::ServerConnection(QObject *parent):
        _parent(parent) {}

void ServerConnection::setHost(const QString &host) {
    _host = host;
}

void ServerConnection::setPort(quint16 port) {
    _port = port;
}

void ServerConnection::setParent(QObject *parent) {
    _parent = parent;
}

void ServerConnection::connect(const QString &username, const QString &password, bool _register) {

}

int ServerConnection::run(void) {
    try {
        _sock = new nw::qt::TCPSocket(_parent);

        _sock->connect(_host.toStdString(), _port);
        return (0);
    } catch (...) {
        return (-1);
    }
}
