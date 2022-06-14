#ifndef MYWIDGET_H
#define MYWIDGET_H
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

class MyWidget : public QWidget
{
    Q_OBJECT
    QSqlDatabase database;
    QLineEdit *le;
    QTextEdit *te;
    QPushButton* btn;
    void connect_sqlite();
private slots:
    void do_query();
public: 
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();
    void opencv();
 };
#endif // MYWIDGET_H
