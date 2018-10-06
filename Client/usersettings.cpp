#include <QFileDialog>
#include "usersettings.h"
#include "ui_usersettings.h"

UserSettings::UserSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserSettings)
{
    ui->setupUi(this);

    this->setMaximumHeight(height());
    connect(this->ui->changeIcon, &QPushButton::clicked, this, &UserSettings::onChangeImageClicked);
}

UserSettings::~UserSettings()
{
    delete ui;
}

void UserSettings::onChangeImageClicked(bool) {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), "", "Images (*.png *.jpg *.jpeg)");


    ui->iconView->setPixmap(QPixmap(filename).scaled(ui->iconView->size(), Qt::IgnoreAspectRatio));
}
