/********************************************************************************
** Form generated from reading UI file 'clientmainwindows.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTMAINWINDOWS_H
#define UI_CLIENTMAINWINDOWS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>
#include "conv.h"
#include "listfrienditem.h"

QT_BEGIN_NAMESPACE

class Ui_ClientMainWindows
{
public:
    QAction *actionAdd_Friend;
    QAction *actionSettings;
    QAction *actionDelete_Friend;
    QAction *actionSettings_2;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    ListFriends *listFriends;
    conv *widget;
    QMenuBar *menuBar;
    QMenu *menuMy_Account;

    void setupUi(QMainWindow *ClientMainWindows)
    {
        if (ClientMainWindows->objectName().isEmpty())
            ClientMainWindows->setObjectName(QStringLiteral("ClientMainWindows"));
        ClientMainWindows->resize(799, 463);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/logo"), QSize(), QIcon::Normal, QIcon::Off);
        ClientMainWindows->setWindowIcon(icon);
        actionAdd_Friend = new QAction(ClientMainWindows);
        actionAdd_Friend->setObjectName(QStringLiteral("actionAdd_Friend"));
        actionSettings = new QAction(ClientMainWindows);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        actionDelete_Friend = new QAction(ClientMainWindows);
        actionDelete_Friend->setObjectName(QStringLiteral("actionDelete_Friend"));
        actionSettings_2 = new QAction(ClientMainWindows);
        actionSettings_2->setObjectName(QStringLiteral("actionSettings_2"));
        centralWidget = new QWidget(ClientMainWindows);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        listFriends = new ListFriends(centralWidget);
        listFriends->setObjectName(QStringLiteral("listFriends"));
        listFriends->setMinimumSize(QSize(260, 0));
        listFriends->setMaximumSize(QSize(260, 16777215));

        horizontalLayout->addWidget(listFriends);

        widget = new conv(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));

        horizontalLayout->addWidget(widget);

        ClientMainWindows->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ClientMainWindows);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 799, 22));
        menuMy_Account = new QMenu(menuBar);
        menuMy_Account->setObjectName(QStringLiteral("menuMy_Account"));
        ClientMainWindows->setMenuBar(menuBar);

        menuBar->addAction(menuMy_Account->menuAction());
        menuMy_Account->addAction(actionAdd_Friend);
        menuMy_Account->addAction(actionDelete_Friend);
        menuMy_Account->addSeparator();
        menuMy_Account->addAction(actionSettings_2);

        retranslateUi(ClientMainWindows);

        QMetaObject::connectSlotsByName(ClientMainWindows);
    } // setupUi

    void retranslateUi(QMainWindow *ClientMainWindows)
    {
        ClientMainWindows->setWindowTitle(QApplication::translate("ClientMainWindows", "Babel", nullptr));
        actionAdd_Friend->setText(QApplication::translate("ClientMainWindows", "Add Friend", nullptr));
        actionSettings->setText(QApplication::translate("ClientMainWindows", "Settings", nullptr));
        actionDelete_Friend->setText(QApplication::translate("ClientMainWindows", "Delete Friend", nullptr));
        actionSettings_2->setText(QApplication::translate("ClientMainWindows", "Settings", nullptr));
        menuMy_Account->setTitle(QApplication::translate("ClientMainWindows", "My Account", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientMainWindows: public Ui_ClientMainWindows {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTMAINWINDOWS_H
