#include <QPainter>
#include <QPalette>
#include "callform.h"
#include "ui_callform.h"

#include <iostream>

QT_BEGIN_NAMESPACE
  extern Q_WIDGETS_EXPORT void qt_blurImage( QPainter *p, QImage &blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0 );
QT_END_NAMESPACE

CallForm::CallForm(QWidget *parent) :
    QDialog(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint),
    ui(new Ui::CallForm)
{
    ui->setupUi(this);

    this->setMaximumSize(this->width(), this->height());
    this->setMinimumSize(this->width(), this->height());
    this->setModal(false);

    QObject::connect(this->ui->buttonCallEnd, &QPushButton::clicked,
                     this, &CallForm::onEndClicked);
}

void    CallForm::onEndClicked(void) {
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
