/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QLineEdit *lineEdit_name;
    QSpacerItem *verticalSpacer;
    QLineEdit *lineEdit_password;
    QCheckBox *checkBoxRemember;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox;
    QPushButton *pushButton;

    void setupUi(QDialog *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QStringLiteral("login"));
        login->resize(355, 193);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/logo"), QSize(), QIcon::Normal, QIcon::Off);
        login->setWindowIcon(icon);
        login->setModal(true);
        verticalLayout_2 = new QVBoxLayout(login);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(25, -1, 25, -1);
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        lineEdit_name = new QLineEdit(login);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));
        lineEdit_name->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lineEdit_name);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        lineEdit_password = new QLineEdit(login);
        lineEdit_password->setObjectName(QStringLiteral("lineEdit_password"));
        lineEdit_password->setEchoMode(QLineEdit::Password);
        lineEdit_password->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lineEdit_password);

        checkBoxRemember = new QCheckBox(login);
        checkBoxRemember->setObjectName(QStringLiteral("checkBoxRemember"));

        verticalLayout->addWidget(checkBoxRemember);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        checkBox = new QCheckBox(login);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(checkBox);

        pushButton = new QPushButton(login);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(0, 35));
        pushButton->setMaximumSize(QSize(150, 16777215));

        horizontalLayout->addWidget(pushButton);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QDialog *login)
    {
        login->setWindowTitle(QApplication::translate("login", "Login", nullptr));
#ifndef QT_NO_TOOLTIP
        lineEdit_name->setToolTip(QApplication::translate("login", "Username", nullptr));
#endif // QT_NO_TOOLTIP
        lineEdit_name->setPlaceholderText(QApplication::translate("login", "Username", nullptr));
#ifndef QT_NO_TOOLTIP
        lineEdit_password->setToolTip(QApplication::translate("login", "Password", nullptr));
#endif // QT_NO_TOOLTIP
        lineEdit_password->setInputMask(QString());
        lineEdit_password->setPlaceholderText(QApplication::translate("login", "Password", nullptr));
        checkBoxRemember->setText(QApplication::translate("login", "Remember password", nullptr));
#ifndef QT_NO_TOOLTIP
        checkBox->setToolTip(QApplication::translate("login", "Use the login bellow to register you", nullptr));
#endif // QT_NO_TOOLTIP
        checkBox->setText(QApplication::translate("login", "Register", nullptr));
        pushButton->setText(QApplication::translate("login", "Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
