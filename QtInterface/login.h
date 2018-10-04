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

private slots:
    void onPacketReceived(babel::protocol::Packet &pack);

    void on_pushButton_clicked();

    void on_login_finished(int result);

private:
    QJsonObject _cr;
    Ui::login   *ui;
};

#endif // LOGIN_H
