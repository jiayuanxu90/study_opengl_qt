#include "window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(texture);
    QApplication a(argc, argv);
    Window w;
    w.show();

    return a.exec();
}
