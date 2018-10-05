/********************************************************************************
** Form generated from reading UI file 'conv.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONV_H
#define UI_CONV_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_conv
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *iconViewer;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelPseudo;
    QLabel *labelName;
    QSpacerItem *horizontalSpacer;
    QPushButton *callButton;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *sendButton;

    void setupUi(QWidget *conv)
    {
        if (conv->objectName().isEmpty())
            conv->setObjectName(QStringLiteral("conv"));
        conv->resize(713, 533);
        conv->setStyleSheet(QLatin1String("QLabel#labelPseudo {\n"
"	font-size: 20px;\n"
"	color: rgb(85, 87, 83);\n"
"}\n"
"QLabel#labelName {\n"
"	font-size: 14px;\n"
"	color: rgb(186, 189, 182);\n"
"}\n"
"QPushButton#callButton {\n"
"	padding: 10px 20px\n"
"}\n"
"QPushButton#sendButton {\n"
"	padding: 5px 15px;\n"
"}\n"
"QPushButton {\n"
"	background-color: transparent;\n"
"    border-style: none;\n"
"    border-radius: 5px;\n"
"}\n"
"QPushButton:hover {\n"
"	background-color: rgb(211, 215, 207);\n"
"}\n"
"QPushButton:pressed {\n"
"	border-style: outset;\n"
"	border-width: 2px;\n"
"	border-color: white;\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(conv);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        iconViewer = new QLabel(conv);
        iconViewer->setObjectName(QStringLiteral("iconViewer"));
        iconViewer->setMinimumSize(QSize(80, 80));
        iconViewer->setMaximumSize(QSize(80, 80));

        horizontalLayout_2->addWidget(iconViewer);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        labelPseudo = new QLabel(conv);
        labelPseudo->setObjectName(QStringLiteral("labelPseudo"));
        labelPseudo->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        verticalLayout_3->addWidget(labelPseudo);

        labelName = new QLabel(conv);
        labelName->setObjectName(QStringLiteral("labelName"));
        labelName->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_3->addWidget(labelName);


        horizontalLayout_2->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        callButton = new QPushButton(conv);
        callButton->setObjectName(QStringLiteral("callButton"));
        callButton->setMinimumSize(QSize(0, 0));
        callButton->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/call"), QSize(), QIcon::Normal, QIcon::Off);
        callButton->setIcon(icon);
        callButton->setIconSize(QSize(20, 20));
        callButton->setFlat(false);

        horizontalLayout_2->addWidget(callButton);


        verticalLayout->addLayout(horizontalLayout_2);

        textEdit = new QTextEdit(conv);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setReadOnly(true);

        verticalLayout->addWidget(textEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        lineEdit = new QLineEdit(conv);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        sendButton = new QPushButton(conv);
        sendButton->setObjectName(QStringLiteral("sendButton"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/send"), QSize(), QIcon::Normal, QIcon::Off);
        sendButton->setIcon(icon1);
        sendButton->setIconSize(QSize(25, 25));

        horizontalLayout->addWidget(sendButton);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(conv);

        QMetaObject::connectSlotsByName(conv);
    } // setupUi

    void retranslateUi(QWidget *conv)
    {
        conv->setWindowTitle(QApplication::translate("conv", "Form", nullptr));
        iconViewer->setText(QString());
        labelPseudo->setText(QApplication::translate("conv", "#JeSuisPseudo", nullptr));
        labelName->setText(QApplication::translate("conv", "#JeSuisUserName", nullptr));
        callButton->setText(QString());
        sendButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class conv: public Ui_conv {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONV_H
