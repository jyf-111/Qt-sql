#ifndef MYWIDGET_H
#define MYWIDGET_H
#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QTabWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QFont>

#include "sql.h"
#include "opencv.h"
#include "sqldialog.h"

#include <memory>

class MyWidget : public QWidget
{
    Q_OBJECT

    std::unique_ptr<sql> sql;
    std::unique_ptr<opencv> opencv;

    std::unique_ptr<QLabel> label;//image
    std::unique_ptr<QTabWidget> tabwidget;

    QTableView* view[3];
    SqlDialog* sqlDialog;
    QPushButton* btn[3];

    std::unique_ptr<QHBoxLayout> Hlayout;
    std::unique_ptr<QVBoxLayout> rightVlayout;
    std::unique_ptr<QVBoxLayout> leftVlayout;

    std::unique_ptr<QHBoxLayout> rightbtnlayout;
    std::unique_ptr<QHBoxLayout> leftbtnlayout;

    QPushButton* fileOpenBtn;

    std::unique_ptr<QLabel> info_label;
    std::unique_ptr<QPushButton> startbtn;
    std::unique_ptr<QPushButton> stopbtn;

    void set_basic_setting();
    void set_layout();
    void set_connect();
    void process();
public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();
};
#endif // MYWIDGET_H
