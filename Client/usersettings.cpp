#include <QFileDialog>
#include <QBuffer>
#include <QPixmap>
#include <QImage>
#include "usersettings.h"
#include "ui_usersettings.h"
#include "singletons.h"
#include "clientprotocol.h"

UserSettings::UserSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserSettings)
{
    ui->setupUi(this);

    this->ui->iconView->setPixmap(
        QPixmap::fromImage(QImage::fromData(reinterpret_cast<uchar*>(
            Singletons::getSrvCo().getClient().icon.data()),
            Singletons::getSrvCo().getClient().icon.size()).scaled(
                ui->iconView->size(),
                Qt::IgnoreAspectRatio)));
    this->setMaximumHeight(height());
    connect(this->ui->changeIcon, &QPushButton::clicked, this, &UserSettings::onChangeImageClicked);

    connect(this->ui->buttonBox, &QDialogButtonBox::accepted, [this] {
        if (this->ui->currentPass->text().isEmpty() == false
        && this->ui->newPass->text().isEmpty() == false)
            this->_userSettings.password = this->ui->currentPass->text();
            this->_userSettings.newPassword = this->ui->newPass->text();
    });
}

UserSettings::~UserSettings()
{
    delete ui;
}

void UserSettings::onChangeImageClicked(bool) {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), "", "Images (*.png *.jpg *.jpeg)");

    if (filename.isEmpty())
        return;
    _userSettings.filename = filename;
    _userSettings.image.clear();
    ui->iconView->setPixmap(QPixmap(filename).scaled(ui->iconView->size(), Qt::IgnoreAspectRatio));
    QBuffer buffer(&_userSettings.image);
    buffer.open(QIODevice::WriteOnly);
    ui->iconView->pixmap()->save(&buffer, "PNG");
}
