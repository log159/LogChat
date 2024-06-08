#include <QApplication>
#include <QSharedMemory>
#include <QTextCodec>

#include "widget.h"
#include "config.h"
#include "configwindow.h"
#include "configlive2d.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    // 设置全局文本编码为UTF-8
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    const QString uniqueKey = QCoreApplication::applicationName();
    QSharedMemory sharedMemory(uniqueKey);

    if (!sharedMemory.create(1)) {

        if (sharedMemory.attach()) {
            sharedMemory.detach();
        }
        return 0;
    }


    Config::init();
    ConfigWindow::init();
    ConfigLive2d::init();
    Widget w;
    w.show();

    return a.exec();
}


