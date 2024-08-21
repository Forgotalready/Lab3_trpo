#include "View/MainWindow.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qApp->setStyle(QStyleFactory::create("Fusion"));
    QFile styleF;

    styleF.setFileName("D:/project/Lab3_trpo/style.qss");
    styleF.open(QFile::ReadOnly);
    QString qssStr = styleF.readAll();

    qApp->setStyleSheet(qssStr);

    MainWindow w;
    w.show();
    return a.exec();
}
