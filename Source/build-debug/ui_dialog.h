/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLabel *label;
    QLineEdit *usernameText;
    QLabel *label_2;
    QLineEdit *portText;
    QLabel *label_3;
    QLineEdit *ipText;
    QDialogButtonBox *okayDialogButton;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(524, 314);
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 60, 321, 17));
        usernameText = new QLineEdit(Dialog);
        usernameText->setObjectName(QStringLiteral("usernameText"));
        usernameText->setGeometry(QRect(30, 90, 321, 27));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 150, 321, 17));
        portText = new QLineEdit(Dialog);
        portText->setObjectName(QStringLiteral("portText"));
        portText->setGeometry(QRect(30, 170, 91, 27));
        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(140, 150, 321, 17));
        ipText = new QLineEdit(Dialog);
        ipText->setObjectName(QStringLiteral("ipText"));
        ipText->setGeometry(QRect(140, 170, 211, 27));
        okayDialogButton = new QDialogButtonBox(Dialog);
        okayDialogButton->setObjectName(QStringLiteral("okayDialogButton"));
        okayDialogButton->setGeometry(QRect(330, 270, 176, 26));
        okayDialogButton->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        label->setText(QApplication::translate("Dialog", "Enter your username:", 0));
        label_2->setText(QApplication::translate("Dialog", "Port", 0));
        label_3->setText(QApplication::translate("Dialog", "IP Address", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
