#include <QApplication>
#include "widget.h"
#include "config.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Config::init();
    Widget w;
    w.show();

    return a.exec();
}


