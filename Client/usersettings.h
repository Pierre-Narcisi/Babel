#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <QDialog>
#include <QByteArray>

namespace Ui {
class UserSettings;
}

class UserSettings : public QDialog
{
    Q_OBJECT

public:
    struct Settings{
        QString     filename;
        QByteArray  image;
        QString     password;
	QString     newPassword;
    };
    explicit UserSettings(QWidget *parent = 0);
    ~UserSettings();

    Settings    &getSettings(void) { return _userSettings; }
private slots:
    void onChangeImageClicked(bool);
private:
    Ui::UserSettings    *ui;
    Settings            _userSettings;
};

#endif // USERSETTINGS_H
