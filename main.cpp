#include <QApplication>
#include "MyWidget.h"
#include <io.h>
#include <direct.h>

int main(int argc, char *argv[])
{
    //mkdir Videos/result
    std::string prefix = "./Videos";
    if(_access(prefix.c_str(),0) == -1){
        _mkdir(prefix.c_str());
    }
    prefix.append("/result");
    qDebug() << QString::fromStdString(prefix);
    if(_access(prefix.c_str(),0) == -1){
        _mkdir(prefix.c_str());
    }

    QApplication app(argc, argv);

    MyWidget* w = new MyWidget;
    w->show();

    return app.exec();
}
