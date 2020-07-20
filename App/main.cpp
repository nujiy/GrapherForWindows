#include <App/APP.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    APP Grapher;
    Grapher.run();

    return a.exec();
}
