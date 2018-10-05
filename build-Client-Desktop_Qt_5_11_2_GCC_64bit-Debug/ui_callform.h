/********************************************************************************
** Form generated from reading UI file 'callform.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALLFORM_H
#define UI_CALLFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CallForm
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *layoutDemand;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *buttonAccept;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *buttonReject;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *layoutOnCall;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *buttonCallEnd;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *CallForm)
    {
        if (CallForm->objectName().isEmpty())
            CallForm->setObjectName(QStringLiteral("CallForm"));
        CallForm->resize(366, 350);
        CallForm->setStyleSheet(QLatin1String("QPushButton {\n"
"	min-width: 50;\n"
"	min-height:50;\n"
"	max-width: 50;\n"
"	max-height:50;\n"
"	border: none;\n"
"	border-radius: 25px;\n"
"	background-color: rgba(136, 138, 133, 0.2);\n"
"	icon-size: 20px;\n"
"}\n"
"\n"
"QPushButton#buttonCallEnd, QPushButton#buttonReject {\n"
"	background-color: rgba(204, 0, 0, 0.2)\n"
"}\n"
"\n"
"QPushButton#buttonCallEnd:hover, QPushButton#buttonReject:hover {\n"
"	background-color: rgb(204, 0, 0)\n"
"}\n"
"\n"
"QPushButton#buttonAccept {\n"
"	background-color: rgba(78, 154, 6, 0.2);\n"
"}\n"
"\n"
"QPushButton#buttonAccept:hover {\n"
"	background-color: rgb(78, 154, 6);\n"
"}"));
        verticalLayout = new QVBoxLayout(CallForm);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        layoutDemand = new QHBoxLayout();
        layoutDemand->setObjectName(QStringLiteral("layoutDemand"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        layoutDemand->addItem(horizontalSpacer_3);

        buttonAccept = new QPushButton(CallForm);
        buttonAccept->setObjectName(QStringLiteral("buttonAccept"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/call"), QSize(), QIcon::Normal, QIcon::Off);
        buttonAccept->setIcon(icon);

        layoutDemand->addWidget(buttonAccept);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        layoutDemand->addItem(horizontalSpacer_5);

        buttonReject = new QPushButton(CallForm);
        buttonReject->setObjectName(QStringLiteral("buttonReject"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/call_end"), QSize(), QIcon::Normal, QIcon::Off);
        buttonReject->setIcon(icon1);

        layoutDemand->addWidget(buttonReject);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        layoutDemand->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(layoutDemand);

        layoutOnCall = new QHBoxLayout();
        layoutOnCall->setObjectName(QStringLiteral("layoutOnCall"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        layoutOnCall->addItem(horizontalSpacer_2);

        buttonCallEnd = new QPushButton(CallForm);
        buttonCallEnd->setObjectName(QStringLiteral("buttonCallEnd"));
        buttonCallEnd->setIcon(icon1);
        buttonCallEnd->setCheckable(false);

        layoutOnCall->addWidget(buttonCallEnd);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        layoutOnCall->addItem(horizontalSpacer);


        verticalLayout->addLayout(layoutOnCall);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(CallForm);

        QMetaObject::connectSlotsByName(CallForm);
    } // setupUi

    void retranslateUi(QDialog *CallForm)
    {
        CallForm->setWindowTitle(QApplication::translate("CallForm", "Dialog", nullptr));
        buttonAccept->setText(QString());
        buttonReject->setText(QString());
        buttonCallEnd->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CallForm: public Ui_CallForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALLFORM_H
