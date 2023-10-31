#include <QApplication>
#include "widget.h"
#include "config.h"
#include "configwindow.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Config::init();
    ConfigWindow::init();
    Widget w;
    w.show();

    return a.exec();
}


