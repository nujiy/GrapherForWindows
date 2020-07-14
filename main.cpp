#include "View/startinterface.h"
#include "View/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    startinterface w;
    w.show();
    return a.exec();
}
