#include <QApplication>
#include <QDebug>

#include "widget.h"
#include "config.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}


