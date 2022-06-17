#include "sqldialog.h"

SqlDialog::SqlDialog():
    sql(new class sql(this)),
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
    textedit->setReadOnly(true);
    lineedit->setFont(QFont("微软雅黑",20));
}

void SqlDialog::set_layout(){
    vlayout->addWidget(textedit);
    vlayout->addWidget(lineedit);
    vlayout->addWidget(btn);
}

void SqlDialog::set_connect(){
    connect(btn,&QPushButton::clicked,[this](){
        textedit->clear();
        QString s = lineedit->text();
        auto vec = sql->do_sql(s);
        for(auto &i:vec){
            QString tmp;
            for(auto j:i){
                tmp.append(j.toString());
                tmp.append(" ");
            }
            textedit->append(tmp);
        }
        QString tmp;
        tmp.append("----------------");
        tmp.append(__TIME__);
        textedit->append(tmp);
        lineedit->clear();
    });
}
