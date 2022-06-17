﻿#include "MyWidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent),
    sql(new class sql(this)),
    opencv(new class opencv),

    label(new QLabel),
    tabwidget(new QTabWidget),
    view{new QTableView,new QTableView,new QTableView},
    sqlDialog(new class SqlDialog),

    fileOpenBtn(new QPushButton("open")),

    btn{new QPushButton("insert"),new QPushButton("delete"),new QPushButton("sql search")},

    startbtn(new QPushButton("start")),
    stopbtn(new QPushButton("stop")),

    info_label(new QLabel("computer:")),

    Hlayout(new QHBoxLayout(this)),
    rightVlayout(new QVBoxLayout),
    leftVlayout(new QVBoxLayout),

    rightbtnlayout(new QHBoxLayout),
    leftbtnlayout(new QHBoxLayout)
{
//登录dialog
    class dialog:public QDialog{
    public:
        std::unique_ptr<QLineEdit> lineedit;
        std::unique_ptr<QPushButton> btn;
        std::unique_ptr<QVBoxLayout> vlayout;
        dialog(QWidget* parent=nullptr):
            QDialog(parent),
            lineedit(new QLineEdit),
            btn(new QPushButton("select")),
            vlayout(new QVBoxLayout(this))
        {
            resize(200,200);
            lineedit->setFont(QFont("微软雅黑",20));
            vlayout->addWidget(lineedit.get());
            vlayout->addWidget(btn.get());

        }
    }dia(this);
    dia.setWindowTitle("computer");
    connect(dia.btn.get(),&QPushButton::clicked,[&](){
        auto text = dia.lineedit->text();
        info_label->setText(text);
        dia.lineedit->clear();
        sql->insert_computer(text);
        dia.close();
    });
    dia.exec();


    set_basic_setting();
    set_layout();
    set_connect();

}

void MyWidget::set_basic_setting(){
    showMaximized();
    label->setPixmap(QPixmap::fromImage(QImage("test.png").scaled(label->width(),label->width())));

    view[0]->setModel(sql->model[0]);
    view[1]->setModel(sql->model[1]);
    view[2]->setModel(sql->model[2]);

    tabwidget->addTab(view[0],"object");
    tabwidget->addTab(view[1],"compter");
    tabwidget->addTab(view[2],"video");
}

void MyWidget::set_layout(){
    //right
    rightVlayout->addWidget(info_label.get());
    rightVlayout->addWidget(tabwidget.get());

    rightbtnlayout->addWidget(fileOpenBtn);
    rightbtnlayout->addWidget(btn[0]);
    rightbtnlayout->addWidget(btn[1]);
    rightbtnlayout->addWidget(btn[2]);
    rightVlayout->addLayout(rightbtnlayout.get());

    leftbtnlayout->addWidget(startbtn.get());
    leftbtnlayout->addWidget(stopbtn.get());

    leftVlayout->addWidget(label.get());
    leftVlayout->addLayout(leftbtnlayout.get());
    leftVlayout->setStretch(0,4);
    leftVlayout->setStretch(1,1);

    Hlayout->addLayout(leftVlayout.get());
    Hlayout->addLayout(rightVlayout.get());
}

MyWidget::~MyWidget()
{
    delete[] view;
    delete sqlDialog;
    delete[] btn;
}

void MyWidget::set_connect(){
    connect(startbtn.get(),&QPushButton::clicked,[&](){
        opencv->qtimer->start();
    });
    connect(stopbtn.get(),&QPushButton::clicked,[&](){
        opencv->qtimer->stop();
    });

    connect(opencv->qtimer,&QTimer::timeout,[this](){
        if(opencv->dispose()){
            label->setPixmap(QPixmap::fromImage(opencv->get_result()));
            auto tmp = opencv->get_tips();
            sql->database.transaction();
            sql->do_sql("delete from object");
            int num = tmp.size();
            for(int i=0;i<num;i++){
                sql->insert_object(i,tmp[i],info_label->text());
            }
            sql->database.commit();
        }
    });
    connect(btn[0],&QPushButton::clicked,[this](){
        auto mod = sql->model[tabwidget->currentIndex()];
        mod->insertRows(0,1);
    });
    connect(btn[1],&QPushButton::clicked,[this](){
        auto num = tabwidget->currentIndex();
        int row = view[num]->currentIndex().row();
        if(QMessageBox::Yes == QMessageBox::question(this,"Make Sure","确定删除第"+QString::number(row+1)+"行吗？",QMessageBox::Yes | QMessageBox::No , QMessageBox::Yes))
            {
            sql->model[num]->removeRow(row);
            sql->model[num]->select();
        }});
    connect(btn[2],&QPushButton::clicked,sqlDialog,&SqlDialog::exec);

    connect(fileOpenBtn,&QPushButton::clicked,[=](){
        QString path = QFileDialog::getOpenFileName(this,"video",".","video(*.avi *.mp4 *.flv)");
        qDebug() << path;
        sql->insert_video(path,0,0);
        opencv->set_video(path);
    });
}
