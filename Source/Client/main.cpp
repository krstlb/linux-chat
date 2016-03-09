#include "mainwindow.h"
#include "stdio.h"
#include <QLabel>
#include <QApplication>
#include <QFile>

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

/* QTextStream& qStdOut()
{
    QTextStream ts( stdout );
    return ts;
} */
