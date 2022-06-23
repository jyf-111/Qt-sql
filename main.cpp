#include <QApplication>
#include "MyWidget.h"
#include <io.h>
#include <direct.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MyWidget* w = new MyWidget;
    w->show();

    return app.exec();
}
