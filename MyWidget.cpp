#include "MyWidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent),
    sql(new class sql),
    //    opencv(new class opencv),
    lineedit(new QLineEdit(this)),
    textedit(new QTextEdit(this)),
    btn(new QPushButton("exec", this)),
    label(new QLabel(this)),
    model(new QSqlTableModel(this,sql->database)),
    view(new QTableView),
    Hlayout(new QHBoxLayout(this)),
    Vlayout(new QVBoxLayout())
{
    set_basic_setting();
    set_layout();
    //    process();
    sql->do_query();
}
void MyWidget::set_basic_setting(){
    resize(1400, 800);
    label->setPixmap(QPixmap::fromImage(QImage("C:/Users/jyf/Pictures/dog.jpg")));
    lineedit->setMaximumHeight(50);
    lineedit->setFont(QFont("微软雅黑",20));
    textedit->setReadOnly(true);

    model->setTable("object");
    model->setHeaderData(1,Qt::Horizontal,"name");
    model->setHeaderData(2,Qt::Horizontal,"number");
    model->select();

    view->setModel(model);
}

void MyWidget::set_layout(){
    //    Vlayout->addWidget(textedit);
    //    Vlayout->addWidget(lineedit);
    //    Vlayout->addWidget(btn);
    //    Vlayout->setStretchFactor(textedit,4);
    //    Vlayout->setStretchFactor(lineedit,1);
    //    Vlayout->setStretchFactor(btn,5);
    Vlayout->addWidget(view);
    Hlayout->addWidget(label);
    Hlayout->addLayout(Vlayout);
}

MyWidget::~MyWidget()
{
}

void MyWidget::process(){
    //    yolo
    connect(opencv->qtimer,&QTimer::timeout,[this](){
        opencv->dispose();
        label->setPixmap(QPixmap::fromImage(opencv->get_result()));
    });
}
