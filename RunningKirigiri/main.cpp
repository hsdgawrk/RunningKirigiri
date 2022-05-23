#include "kirigiritray.h"

#include <QApplication>
#include <QResource>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //注册资源(目前为gif图)编译为rcc文件减少资源占用
    QResource::registerResource("res.rcc");

    KirigiriTray w;

    return a.exec();
}
