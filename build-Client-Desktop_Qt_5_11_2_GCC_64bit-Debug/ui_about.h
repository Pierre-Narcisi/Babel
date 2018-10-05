/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout;
    QLabel *labelVersionText;
    QLabel *labelVersion;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonOk;

    void setupUi(QDialog *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName(QStringLiteral("About"));
        About->setWindowModality(Qt::NonModal);
        About->resize(360, 217);
        About->setModal(true);
        verticalLayout = new QVBoxLayout(About);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        textEdit = new QTextEdit(About);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setReadOnly(true);

        verticalLayout->addWidget(textEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelVersionText = new QLabel(About);
        labelVersionText->setObjectName(QStringLiteral("labelVersionText"));
        labelVersionText->setMaximumSize(QSize(10000, 16777215));

        horizontalLayout->addWidget(labelVersionText);

        labelVersion = new QLabel(About);
        labelVersion->setObjectName(QStringLiteral("labelVersion"));

        horizontalLayout->addWidget(labelVersion);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonOk = new QPushButton(About);
        buttonOk->setObjectName(QStringLiteral("buttonOk"));

        horizontalLayout->addWidget(buttonOk);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(About);

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QDialog *About)
    {
        About->setWindowTitle(QApplication::translate("About", "About", nullptr));
        textEdit->setHtml(QApplication::translate("About", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; font-weight:600;\">Babel Client</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">License:</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; marg"
                        "in-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Have you heard about the Beer Public License Agreement yet ?</p></body></html>", nullptr));
        labelVersionText->setText(QApplication::translate("About", "Version: ", nullptr));
        labelVersion->setText(QApplication::translate("About", "0.0.0", nullptr));
        buttonOk->setText(QApplication::translate("About", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
