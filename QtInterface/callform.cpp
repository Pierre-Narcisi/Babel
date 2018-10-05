#include <QPainter>
#include <QPalette>
#include <QMessageBox>
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

    this->setMaximumSize(this->width(), this->height());
    this->setMinimumSize(this->width(), this->height());
    this->setModal(false);

    this->setAttribute(Qt::WA_DeleteOnClose, true);
    QObject::connect(this->ui->buttonCallEnd, &QPushButton::clicked,
                    this, &CallForm::onEndClicked);
    QObject::connect(this->ui->buttonReject, &QPushButton::clicked,
                    this, &CallForm::onRejectClicked);
    QObject::connect(&Singletons::getSrvCo(), &client::protocol::ClientSender::onPacketReceived,
                    this, &CallForm::onPacketReceived);
}

void    CallForm::onPacketReceived(babel::protocol::Packet &pack) {
    auto &p = reinterpret_cast<babel::protocol::Respond&>(pack);
    auto &r = reinterpret_cast<babel::protocol::CallRespond&>(pack);

    if ((pack.type == babel::protocol::Packet::Type::Respond)
    && (p.previous == babel::protocol::Packet::Type::CallRequest)) {
        if (p.respond == babel::protocol::Respond::KO) {
            QMessageBox::information(this, "Call failed: ", QString::fromLatin1(p.data));
            this->close();
        }
    } else if (pack.type == babel::protocol::Packet::Type::CallRespond
    && (_f->username.toStdString() == std::string(r.username))) {
        if (r.respond == babel::protocol::CallRespond::REJECT) {
            this->close();
        }
    }
}

void    CallForm::onEndClicked(void) {
    this->close();
}

void    CallForm::onRejectClicked(void) {
    this->close();
}

CallForm::~CallForm()
{
    delete ui;
}

void    CallForm::setFriendInfo(FriendsManager::FriendInfo *f) {
    _f = f;
    this->setWindowTitle("Call -- " + _f->pseudo);
}

void    CallForm::showEvent(QShowEvent *e) {
    Q_UNUSED(e)

    _paintBlurImage();
    if (!_isDemand) {
        babel::protocol::CallRequest    pack;
        std::strcpy(pack.username, _f->username.toStdString().c_str());

        Singletons::getSrvCo().sendPacket(pack);
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

void    CallForm::_paintBlurImage(void) {
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
                    this->size(),
                    Qt::KeepAspectRatioByExpanding));
    this->setPalette(palette);
}
