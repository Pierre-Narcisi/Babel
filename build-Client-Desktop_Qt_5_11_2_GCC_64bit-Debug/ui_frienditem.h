/********************************************************************************
** Form generated from reading UI file 'frienditem.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDITEM_H
#define UI_FRIENDITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FriendItem
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *FriendImg;
    QLabel *FriendNameLabel;
    QPushButton *stateIndicator;

    void setupUi(QWidget *FriendItem)
    {
        if (FriendItem->objectName().isEmpty())
            FriendItem->setObjectName(QStringLiteral("FriendItem"));
        FriendItem->resize(398, 60);
        FriendItem->setMinimumSize(QSize(0, 60));
        FriendItem->setMaximumSize(QSize(16777215, 60));
        FriendItem->setStyleSheet(QLatin1String("QWidget#FriendItem:hover {\n"
"	background-color: rgb(200, 200, 200);\n"
"}\n"
"QWidget#FriendItem[selectedItem=\"true\"] {\n"
"	background-color: rgb(114, 159, 207);\n"
"}\n"
"QLabel#FriendIcon {\n"
"	background-color: transparent;\n"
"}"));
        horizontalLayout = new QHBoxLayout(FriendItem);
        horizontalLayout->setSpacing(8);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 8, 0);
        FriendImg = new QLabel(FriendItem);
        FriendImg->setObjectName(QStringLiteral("FriendImg"));
        FriendImg->setMinimumSize(QSize(60, 0));
        FriendImg->setMaximumSize(QSize(60, 16777215));
        FriendImg->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(FriendImg);

        FriendNameLabel = new QLabel(FriendItem);
        FriendNameLabel->setObjectName(QStringLiteral("FriendNameLabel"));
        FriendNameLabel->setStyleSheet(QLatin1String("QLabel {\n"
"	background-color: transparent;\n"
"	color: rgb(85, 87, 83);\n"
"	\n"
"	font: 75 13pt \"Noto Sans CJK SC\";\n"
"}\n"
"\n"
"QLabel[selectedItem=\"true\"] {\n"
"		color: rgb(250, 250, 250);\n"
"}"));
        FriendNameLabel->setWordWrap(true);

        horizontalLayout->addWidget(FriendNameLabel);

        stateIndicator = new QPushButton(FriendItem);
        stateIndicator->setObjectName(QStringLiteral("stateIndicator"));
        stateIndicator->setStyleSheet(QLatin1String("QPushButton {\n"
"	max-width: 6px;\n"
"	max-height: 6px;\n"
"	border: none;\n"
"	border-radius: 3px;\n"
"	background-color: red;\n"
"}\n"
"QPushButton[connected=\"true\"]{\n"
"	background-color: green;\n"
"}"));

        horizontalLayout->addWidget(stateIndicator);


        retranslateUi(FriendItem);

        QMetaObject::connectSlotsByName(FriendItem);
    } // setupUi

    void retranslateUi(QWidget *FriendItem)
    {
        FriendItem->setWindowTitle(QApplication::translate("FriendItem", "Form", nullptr));
        FriendImg->setText(QString());
        FriendNameLabel->setText(QApplication::translate("FriendItem", "Name", nullptr));
        stateIndicator->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FriendItem: public Ui_FriendItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDITEM_H
