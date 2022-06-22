#include "sqldialog.h"

SqlDialog::SqlDialog(QWidget* parent):
    QDialog(parent),
    sql(static_cast<MyWidget*>(parent)->sql),
    textedit(new QTextEdit),
    lineedit(new QLineEdit),
    btn(new QPushButton("exec")),
    vlayout(new QVBoxLayout(this))
{
    basic_setting();
    set_layout();
    set_connect();
}

void SqlDialog::basic_setting(){
    setWindowTitle("sql exec");
    textedit->setReadOnly(true);
    lineedit->setFont(QFont("微软雅黑",20));
}

void SqlDialog::set_layout(){
    vlayout->addWidget(textedit.get());
    vlayout->addWidget(lineedit.get());
    vlayout->addWidget(btn.get());
}

void SqlDialog::set_connect(){
    connect(btn.get(),&QPushButton::clicked,[this](){
        textedit->clear();
        QString s = lineedit->text();
        auto vec = sql->do_sql(s);
        textedit->append(QString("> ").append(s));
        for(auto &i:vec){
            QString tmp;
            for(auto j:i){
                tmp.append(j.toString());
                tmp.append(" ");
            }
            textedit->append(tmp);
        }
        QString tmp;
        tmp.append("---------------------------");
        textedit->append(tmp);
        lineedit->clear();
    });
}
