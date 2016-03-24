/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionSettings;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QListWidget *listWidget;
    QTextBrowser *textWindow;
    QLineEdit *sendMessageContent;
    QPushButton *sendDataButton;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_5;
    QLabel *connectionLabel;
    QLabel *label;
    QPushButton *exportFileButton;
    QWidget *tab_2;
    QLineEdit *usernameField;
    QLineEdit *ipField;
    QLineEdit *portField;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButton;
    QPushButton *disconnectButton;
    QPushButton *disconnectButton_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(887, 583);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setWindowOpacity(1);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        actionConnect->setCheckable(true);
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setStyleSheet(QStringLiteral(""));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        listWidget = new QListWidget(tab);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(10, 40, 171, 471));
        listWidget->setMinimumSize(QSize(0, 0));
        listWidget->setMaximumSize(QSize(171, 16777215));
        QFont font;
        font.setFamily(QStringLiteral("Droid Sans"));
        font.setPointSize(15);
        listWidget->setFont(font);
        listWidget->setSelectionMode(QAbstractItemView::NoSelection);
        textWindow = new QTextBrowser(tab);
        textWindow->setObjectName(QStringLiteral("textWindow"));
        textWindow->setGeometry(QRect(200, 40, 651, 401));
        textWindow->setMinimumSize(QSize(316, 181));
        QFont font1;
        font1.setFamily(QStringLiteral("Droid Sans"));
        font1.setPointSize(16);
        textWindow->setFont(font1);
        textWindow->setAutoFillBackground(false);
        textWindow->setTextInteractionFlags(Qt::NoTextInteraction);
        sendMessageContent = new QLineEdit(tab);
        sendMessageContent->setObjectName(QStringLiteral("sendMessageContent"));
        sendMessageContent->setGeometry(QRect(200, 460, 551, 51));
        sendMessageContent->setFont(font1);
        sendDataButton = new QPushButton(tab);
        sendDataButton->setObjectName(QStringLiteral("sendDataButton"));
        sendDataButton->setEnabled(true);
        sendDataButton->setGeometry(QRect(760, 460, 91, 51));
        QFont font2;
        font2.setFamily(QStringLiteral("Droid Sans"));
        font2.setBold(true);
        font2.setItalic(false);
        font2.setWeight(75);
        sendDataButton->setFont(font2);
        sendDataButton->setStyleSheet(QLatin1String("background-color: #748BD9;\n"
"color: rgb(208, 208, 208);"));
        sendDataButton->setFlat(false);
        horizontalLayoutWidget = new QWidget(tab);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 291, 21));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(horizontalLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        QFont font3;
        font3.setBold(true);
        font3.setWeight(75);
        label_5->setFont(font3);

        horizontalLayout->addWidget(label_5);

        connectionLabel = new QLabel(horizontalLayoutWidget);
        connectionLabel->setObjectName(QStringLiteral("connectionLabel"));
        QFont font4;
        font4.setBold(false);
        font4.setWeight(50);
        connectionLabel->setFont(font4);
        connectionLabel->setStyleSheet(QStringLiteral("color: rgb(255, 0, 12);"));

        horizontalLayout->addWidget(connectionLabel);

        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font3);

        horizontalLayout->addWidget(label);

        exportFileButton = new QPushButton(tab);
        exportFileButton->setObjectName(QStringLiteral("exportFileButton"));
        exportFileButton->setGeometry(QRect(740, 0, 111, 31));
        exportFileButton->setStyleSheet(QLatin1String("background-color: #748BD9;\n"
"font: bold;"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        usernameField = new QLineEdit(tab_2);
        usernameField->setObjectName(QStringLiteral("usernameField"));
        usernameField->setGeometry(QRect(190, 130, 421, 51));
        QFont font5;
        font5.setPointSize(16);
        usernameField->setFont(font5);
        ipField = new QLineEdit(tab_2);
        ipField->setObjectName(QStringLiteral("ipField"));
        ipField->setGeometry(QRect(190, 240, 301, 51));
        ipField->setFont(font5);
        portField = new QLineEdit(tab_2);
        portField->setObjectName(QStringLiteral("portField"));
        portField->setGeometry(QRect(500, 240, 111, 51));
        portField->setFont(font5);
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(190, 100, 241, 17));
        QFont font6;
        font6.setFamily(QStringLiteral("Droid Sans"));
        font6.setPointSize(13);
        label_2->setFont(font6);
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(190, 210, 111, 17));
        label_3->setFont(font6);
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(500, 210, 67, 17));
        label_4->setFont(font6);
        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(500, 310, 111, 51));
        QFont font7;
        font7.setFamily(QStringLiteral("Droid Sans"));
        font7.setPointSize(12);
        font7.setBold(true);
        font7.setItalic(false);
        font7.setWeight(75);
        pushButton->setFont(font7);
        pushButton->setStyleSheet(QLatin1String("background-color: #748BD9;\n"
"font: bold;"));
        disconnectButton = new QPushButton(tab_2);
        disconnectButton->setObjectName(QStringLiteral("disconnectButton"));
        disconnectButton->setGeometry(QRect(350, 310, 141, 51));
        disconnectButton->setFont(font7);
        disconnectButton->setStyleSheet(QLatin1String("background-color: #748BD9;\n"
"font: bold;"));
        disconnectButton_2 = new QPushButton(tab_2);
        disconnectButton_2->setObjectName(QStringLiteral("disconnectButton_2"));
        disconnectButton_2->setGeometry(QRect(190, 310, 151, 51));
        disconnectButton_2->setFont(font7);
        disconnectButton_2->setStyleSheet(QLatin1String("background-color: #748BD9;\n"
"font: bold;"));
        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        sendDataButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Linux Chat Application | Oscar & Krystle", 0));
        actionConnect->setText(QApplication::translate("MainWindow", "Connect", 0));
        actionDisconnect->setText(QApplication::translate("MainWindow", "Disconnect", 0));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings", 0));
        sendDataButton->setText(QApplication::translate("MainWindow", "Send", 0));
        label_5->setText(QApplication::translate("MainWindow", "Users:", 0));
        connectionLabel->setText(QApplication::translate("MainWindow", "      Offline", 0));
        label->setText(QApplication::translate("MainWindow", "Chat window:", 0));
        exportFileButton->setText(QApplication::translate("MainWindow", "Export to file", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Chat", 0));
        label_2->setText(QApplication::translate("MainWindow", "Enter your username", 0));
        label_3->setText(QApplication::translate("MainWindow", "IP Address", 0));
        label_4->setText(QApplication::translate("MainWindow", "Port", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Connect", 0));
        disconnectButton->setText(QApplication::translate("MainWindow", "Disconnect", 0));
        disconnectButton_2->setText(QApplication::translate("MainWindow", "Default", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Connect", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
