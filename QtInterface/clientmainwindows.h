#ifndef LAUNCHERMAINWINDOWS_H
#define LAUNCHERMAINWINDOWS_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QKeyEvent>
#include <memory>
#include "Opts/Opts.hpp"
#include "frienditem.h"
#include "serverconnection.h"

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

private:
    void    closeEvent(QCloseEvent *event);
    void    showEvent(QShowEvent *event);

    ::common::Opts          &_opts;
    ServerConnection        *_srv;
    Ui::ClientMainWindows   *ui;
};

#endif // LAUNCHERMAINWINDOWS_H
