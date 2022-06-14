#include <QApplication>
#include "MyWidget.h"

using namespace cv;
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MyWidget* w = new MyWidget;
    w->show();
    w->opencv();
    return app.exec();
}
