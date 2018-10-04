#ifndef CONV_H
#define CONV_H

#include <QWidget>

namespace Ui {
class conv;
}

class conv : public QWidget
{
    Q_OBJECT

public:
    explicit conv(QWidget *parent = nullptr);
    ~conv();

private slots:
    void on_callButton_clicked();

private:
    Ui::conv *ui;
};

#endif // CONV_H
