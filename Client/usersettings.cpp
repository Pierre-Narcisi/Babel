#include <QFileDialog>
#include <QBuffer>
#include "usersettings.h"
#include "ui_usersettings.h"

UserSettings::UserSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserSettings)
{
    ui->setupUi(this);

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
