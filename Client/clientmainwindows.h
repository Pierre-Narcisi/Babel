#ifndef LAUNCHERMAINWINDOWS_H
#define LAUNCHERMAINWINDOWS_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QKeyEvent>
#include <memory>
#include "Opts/Opts.hpp"
#include "frienditem.h"
#include "clientprotocol.h"
#include "call.h"

namespace Ui {
class ClientMainWindows;
}

class ClientMainWindows : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientMainWindows(QWidget *parent, common::Opts &opts);
    ~ClientMainWindows();

public slots:
    void    onDisconnectClicked(bool);

private:
    void    closeEvent(QCloseEvent *event);
    void    showEvent(QShowEvent *event);

    common::Opts                    &_opts;
    client::protocol::ClientSender  &_srvCo;
    Ui::ClientMainWindows           *ui;
};

#endif // LAUNCHERMAINWINDOWS_H
