#include <QPainter>
#include <QPalette>
#include <QMessageBox>
#include <QApplication>
#include <QGuiApplication>
#include <QHostAddress>
#include <QScreen>
#include <QResizeEvent>
#include <cstring>
#include "callform.h"
#include "ui_callform.h"
#include "singletons.h"

#include <iostream>

QT_BEGIN_NAMESPACE
  extern Q_WIDGETS_EXPORT void qt_blurImage(QPainter *p, QImage &blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0);
QT_END_NAMESPACE

CallForm::CallForm(QWidget *parent, bool isDemand) :
    QDialog(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint),
    _isDemand(isDemand),
    ui(new Ui::CallForm)
{
    ui->setupUi(this);

    //this->setMaximumSize(this->width(), this->height());
    this->setMinimumSize(this->width(), this->height());
    this->setModal(false);

    if (!parent) {
        QRect rec = QGuiApplication::screenAt(this->geometry().topLeft())->virtualGeometry();
        this->move((rec.width() - this->width()) / 2,
                   (rec.height() - this->height()) / 2);
    }
    if (_isDemand) {
        _isInit = true;
    }
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    QObject::connect(this->ui->buttonCallEnd, &QPushButton::clicked,
                    this, &CallForm::onEndClicked);
    QObject::connect(this->ui->buttonReject, &QPushButton::clicked,
                    this, &CallForm::onRejectClicked);
    QObject::connect(this->ui->buttonAccept, &QPushButton::clicked,
                    this, &CallForm::onAcceptClicked);
    QObject::connect(&Singletons::getSrvCo(), &client::protocol::ClientSender::onPacketReceived,
                    this, &CallForm::onPacketReceived);
    _registerCallEnd();
}

CallForm::~CallForm()
{
    delete ui;
}

void    CallForm::onPacketReceived(babel::protocol::Packet &pack) {
    auto &p = reinterpret_cast<babel::protocol::Respond&>(pack);
    auto &r = reinterpret_cast<babel::protocol::CallRespond&>(pack);

    if ((_isInit== false)
    && (pack.type == babel::protocol::Packet::Type::Respond)
    && (p.previous == babel::protocol::Packet::Type::CallRequest)) {
        if (p.respond == babel::protocol::Respond::KO) {
            QMessageBox::information(this, "Call failed: ", QString::fromLatin1(p.data));
            this->close();
        }
        _isInit = true;
    } else if ((pack.type == babel::protocol::Packet::Type::Respond)
    && (p.previous == babel::protocol::Packet::Type::CallRespond)) {
        if (p.respond == babel::protocol::Respond::OK) {
            _initCall();
            _isDemand = false;
        }
    } else if (pack.type == babel::protocol::Packet::Type::CallRespond
    && (_f->username.toStdString() == std::string(r.fromUsername))) {
        if (r.respond == babel::protocol::CallRespond::REJECT) {
            this->close();
        } else {
            _initCall();
        }
    } else if ((pack.type == babel::protocol::Packet::Type::Respond)
    && (p.previous == babel::protocol::Packet::Type::GetClientIp)) {
        auto *data = reinterpret_cast<proto::data::GetClientIpRespond*>(p.data);
        if (_f->username.toStdString() != data->username)
            return;
        if (p.respond == babel::protocol::Respond::OK) {
            QHostAddress ip(data->ip);
            QMessageBox::information(this, "remote ip: ", ip.toString());
        } else {
            QMessageBox::information(this, "Call failed: ", QString::fromLatin1(p.data));
            this->close();
        }
    }
}

void    CallForm::onEndClicked(void) {
    babel::protocol::CallEnd    pack;
    auto                        &co = Singletons::getSrvCo();

    std::strcpy(pack.username, _f->username.toStdString().c_str());

    co.sendPacket(pack);
    this->close();
}

void    CallForm::onRejectClicked(void) {
    babel::protocol::CallRespond    pack;
    auto                            &co = Singletons::getSrvCo();

    std::strcpy(pack.fromUsername, co.getClient().username.toStdString().c_str());
    std::strcpy(pack.toUsername, _f->username.toStdString().c_str());
    pack.respond = babel::protocol::CallRespond::REJECT;

    co.sendPacket(pack);
    this->close();
}

void    CallForm::onAcceptClicked(void) {
    babel::protocol::CallRespond    pack;
    auto                            &co = Singletons::getSrvCo();

    std::strcpy(pack.fromUsername, co.getClient().username.toStdString().c_str());
    std::strcpy(pack.toUsername, _f->username.toStdString().c_str());
    pack.respond = babel::protocol::CallRespond::ACCEPT;

    co.sendPacket(pack);
}

void    CallForm::onCallEnd(QString name) {
    if (name == _f->username)
        this->close();
}

void    CallForm::_initCall(void) {
    babel::protocol::GetClientIp    pack;
    auto                            &co = Singletons::getSrvCo();

    std::strcpy(pack.username, _f->username.toStdString().c_str());
    co.sendPacket(pack);
}

void    CallForm::_registerCallEnd(void) {
    QObject::connect(&Singletons::getSrvCo(), &client::protocol::ClientSender::onCallEnd,
                     this, &CallForm::onCallEnd);
}

void    CallForm::setFriendInfo(FriendsManager::FriendInfo *f) {
    _f = f;
    this->setWindowTitle("Call -- " + _f->pseudo);
}

void    CallForm::showEvent(QShowEvent *e) {
    Q_UNUSED(e)

    if (!_isDemand) {
        babel::protocol::CallRequest    pack;
        std::strcpy(pack.username, _f->username.toStdString().c_str());

        Singletons::getSrvCo().sendPacket(pack);
    } else {
        this->activateWindow();
        this->raise();
    }
}

void    CallForm::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e)

    static auto __setVisible = [] (QBoxLayout *lay, bool visible) {
        for (auto i = 0; i < lay->count(); i++) {
            auto *itm = lay->itemAt(i);

            if (!(dynamic_cast<QWidgetItem*>(itm)))
                continue;
            if (visible)
                itm->widget()->show();
            else
                itm->widget()->hide();
        }
    };

    if (_isDemand) {
       __setVisible(this->ui->layoutDemand, true);
       __setVisible(this->ui->layoutOnCall, false);
    } else {
       __setVisible(this->ui->layoutDemand, false);
       __setVisible(this->ui->layoutOnCall, true);
    }
}

void    CallForm::resizeEvent(QResizeEvent *e) {
    _paintBlurImage(e->size());
}

void    CallForm::_paintBlurImage(QSize const &newSize) {
    auto bkgnd = _f->icon;

    QPixmap pxDst(bkgnd.size());
    pxDst.fill(Qt::transparent);
    {
        QPainter painter(&pxDst);
        qt_blurImage(&painter, bkgnd, 400, true, false);
    }
    QPalette palette;
    palette.setBrush(
                QPalette::Background,
                bkgnd.scaled(
                    newSize,
                    Qt::IgnoreAspectRatio));
    this->setPalette(palette);
}
