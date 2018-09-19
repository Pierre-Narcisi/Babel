#ifndef LAUNCHERMAINWINDOWS_H
#define LAUNCHERMAINWINDOWS_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QKeyEvent>
#include "Json/Entity.hpp"
#include "frienditem.h"

namespace Ui {
class ClientMainWindows;
}

class ClientMainWindows : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientMainWindows(QWidget *parent = 0);
    ~ClientMainWindows();

private:
    void    closeEvent(QCloseEvent *event);

    Ui::ClientMainWindows *ui;
    json::Entity            _settings;

public slots:
    //void    updatePrintData(FriendItem *);
};

#endif // LAUNCHERMAINWINDOWS_H
