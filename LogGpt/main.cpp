#include <QApplication>
#include <QSharedMemory>

#include "widget.h"
#include "config.h"
#include "configwindow.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    // 使用应用程序名称创建唯一的共享内存键
    const QString uniqueKey = QCoreApplication::applicationName();
    // 创建共享内存对象
    QSharedMemory sharedMemory(uniqueKey);

    // 检查是否已经有一个实例在运行
    if (!sharedMemory.create(1)) {
        // 如果共享内存已经存在，说明已经有一个实例在运行
        if (sharedMemory.attach()) {

            // 释放共享内存
            sharedMemory.detach();
        }

        // 退出应用程序
        return 0;
    }


    Config::init();
    ConfigWindow::init();
    Widget w;
    w.show();

    return a.exec();
}


