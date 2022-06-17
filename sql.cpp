#include "sql.h"

sql::sql(QWidget* parent)
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        // 建立和SQlite数据库的连接
        database = QSqlDatabase::addDatabase("QSQLITE");
        // 设置数据库文件的名字
        database.setDatabaseName("test.db");
    }
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        qDebug() << "success";
    }

    model[0] = new QSqlTableModel(parent,database);
    model[1] = new QSqlTableModel(parent,database);
    model[2] = new QSqlTableModel(parent,database);
    basic_setting();
}

sql::~sql(){
    database.close();
}

void sql::basic_setting(){
    model[0]->setTable("object");
    model[0]->setEditStrategy(QSqlTableModel::OnFieldChange);
    model[0]->setHeaderData(0,Qt::Horizontal,"index");
    model[0]->setHeaderData(1,Qt::Horizontal,"name");
    model[0]->select();

    model[1]->setTable("computer");
    model[1]->setEditStrategy(QSqlTableModel::OnFieldChange);
    model[1]->setHeaderData(0,Qt::Horizontal,"name");
    model[1]->setHeaderData(1,Qt::Horizontal,"CPU");
    model[1]->setHeaderData(2,Qt::Horizontal,"GPU");
    model[1]->select();

    model[2]->setTable("video");
    model[2]->setEditStrategy(QSqlTableModel::OnFieldChange);
    model[2]->setHeaderData(0,Qt::Horizontal,"name");
    model[2]->setHeaderData(1,Qt::Horizontal,"size");
    model[2]->setHeaderData(2,Qt::Horizontal,"time");
    model[2]->select();
}

auto sql::do_sql(QString s)->std::vector<std::vector<QVariant>>
{
    std::vector<std::vector<QVariant>> result;
    QSqlQuery query(database);
    std::vector<QVariant> tmp;
    if(s.size()==0 || !query.exec(s)){
        qDebug() << "query fail";
        tmp.push_back(query.lastError().text());
        result.push_back(tmp);
    }else{
        while (query.next())
        {
            tmp.clear();
            tmp.push_back(query.value(0));
            tmp.push_back(query.value(1));
            result.push_back(tmp);
        }
    }
    return result;
}


void sql::insert_object(int num,QString s,QString com){
    model[0]->insertRows(0,1);
    model[0]->setData(model[0]->index(0,0),num);
    model[0]->setData(model[0]->index(0,1),s);
    model[0]->setData(model[0]->index(0,2),com);
    model[0]->submitAll();
    model[0]->select();
}

void sql::insert_computer(QString s){
    model[1]->insertRows(0,1);
    model[1]->setData(model[1]->index(0,0),s);
    model[1]->setData(model[1]->index(0,1),"");
    model[1]->setData(model[1]->index(0,2),"");
    model[1]->submitAll();
    model[1]->select();
}

void sql::insert_video(QString s,int size,int time){
    model[2]->insertRows(0,1);
    model[2]->setData(model[2]->index(0,0),s);
    model[2]->setData(model[2]->index(0,1),size);
    model[2]->setData(model[2]->index(0,2),time);
    model[2]->submitAll();
    model[2]->select();
}

