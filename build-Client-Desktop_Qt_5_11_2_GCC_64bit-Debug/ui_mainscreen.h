/********************************************************************************
** Form generated from reading UI file 'mainscreen.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINSCREEN_H
#define UI_MAINSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainscreen
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;

    void setupUi(QWidget *mainscreen)
    {
        if (mainscreen->objectName().isEmpty())
            mainscreen->setObjectName(QStringLiteral("mainscreen"));
        mainscreen->resize(656, 463);
        horizontalLayout = new QHBoxLayout(mainscreen);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget = new QWidget(mainscreen);
        widget->setObjectName(QStringLiteral("widget"));

        horizontalLayout->addWidget(widget);


        retranslateUi(mainscreen);

        QMetaObject::connectSlotsByName(mainscreen);
    } // setupUi

    void retranslateUi(QWidget *mainscreen)
    {
        mainscreen->setWindowTitle(QApplication::translate("mainscreen", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainscreen: public Ui_mainscreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINSCREEN_H
