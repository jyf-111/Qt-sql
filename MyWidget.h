#ifndef MYWIDGET_H
#define MYWIDGET_H
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include "sql.h"
#include "opencv.h"

class MyWidget : public QWidget
{
    Q_OBJECT

    sql* sql;
    opencv* opencv;

    QLineEdit *lineedit;
    QTextEdit *textedit;
    QPushButton *btn;
    QLabel *label;
    QSqlTableModel *model;
    QTableView *view;
    QVBoxLayout *Vlayout;
    QHBoxLayout *Hlayout;

    void set_basic_setting();
    void set_layout();
    void process();
public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();
};
#endif // MYWIDGET_H
