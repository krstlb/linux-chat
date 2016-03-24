#include "mainwindow.h"
#include "stdio.h"
#include <QLabel>
#include <QApplication>
#include <QFile>

/*---------------------------------------------------------------------------------------
--  SOURCE FILE:    main.cpp
--
--  PROGRAM:        Linux Chat application
--
--  FUNCTIONS:
--
--      int main(int argc, char *argv[])
--
--
--  DATE:           March 23, 2016
--
--  REVISIONS:      (Date and Description)
--
--  DESIGNERS:      Oscar Kwan
--
--  PROGRAMMER:     Oscar Kwan
--
--  NOTES:`
---------------------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;    

    QFile file(":qdarkstyle/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    a.setStyleSheet(styleSheet);

    w.show();

    return a.exec();
}
