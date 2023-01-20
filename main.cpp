#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file;
    file.setFileName(":/new/prefix1/style.css");
    if (!file.open(QFile::ReadOnly))
        qDebug() << "ERROR CSS FILE: CANNOT OPEN";
    else
        a.setStyleSheet(QLatin1String(file.readAll()));

    MainWindow w;
    w.show();

    return a.exec();
}
