#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QJsonObject>
#include <QJsonValue>

namespace Ui {
class login;
}

namespace babel { namespace protocol {
class Packet;
}}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

    void    setCannotAutoConnect(bool);

private slots:
    void onPacketReceived(babel::protocol::Packet &pack);

    void on_pushButton_clicked();

    void on_login_finished(int result);

private:
    void    showEvent(QShowEvent *);

private:
    QJsonObject _cr;
    Ui::login   *ui;
    bool        _cannotAutoConnect = false;
};

#endif // LOGIN_H
