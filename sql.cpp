#include "sql.h"

sql::sql()
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
        database.setDatabaseName("data.db");
    }
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        qDebug() << "connect database success";
    }

    model[0] = new QSqlTableModel(nullptr,database);
    model[1] = new QSqlTableModel(nullptr,database);
    model[2] = new QSqlTableModel(nullptr,database);
    basic_setting();
    do_sql("delete from object");
}

sql::~sql(){
    database.close();
}

void sql::basic_setting(){
    model[0]->setTable("object");
    model[0]->setEditStrategy(QSqlTableModel::OnFieldChange);
    model[0]->setHeaderData(0,Qt::Horizontal,"idx");
    model[0]->setHeaderData(1,Qt::Horizontal,"oname");
    model[0]->setHeaderData(2,Qt::Horizontal,"cname");
    model[0]->select();

    model[1]->setTable("computer");
    model[1]->setEditStrategy(QSqlTableModel::OnFieldChange);
    model[1]->setHeaderData(0,Qt::Horizontal,"cname");
    model[1]->setHeaderData(1,Qt::Horizontal,"CPU");
    model[1]->setHeaderData(2,Qt::Horizontal,"GPU");
    model[1]->select();

    model[2]->setTable("video");
    model[2]->setEditStrategy(QSqlTableModel::OnFieldChange);
    model[2]->setHeaderData(0,Qt::Horizontal,"vname");
    model[2]->setHeaderData(1,Qt::Horizontal,"width");
    model[2]->setHeaderData(2,Qt::Horizontal,"height");
    model[2]->setHeaderData(3,Qt::Horizontal,"cname");
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
            int i = 0;
            QVariant val;

            while((val=query.value(i++)).isValid()) 
                tmp.push_back(val.toString());
            result.push_back(tmp);
        }
    }
    return result;
}


void sql::insert_object(int num,QString s,QString cname){
    QSqlRecord record = model[0]->record();
    record.setValue(0,num);
    record.setValue(1,s);
    record.setValue(2,cname);
    model[0]->insertRecord(0,record);
    model[0]->submitAll();
    model[0]->select();
}

void sql::insert_computer(QString s){
    QSqlRecord record = model[1]->record();
    record.setValue(0,s);
    record.setNull(1);
    record.setNull(2);
    model[1]->insertRecord(0,record);
    model[1]->submitAll();
    model[1]->select();
}

void sql::insert_video(QString s,int width,int height,QString cname){
    QSqlRecord record = model[2]->record();
    record.setValue(0,s);
    record.setValue(1,width);
    record.setValue(2,height);
    record.setValue(3,cname);
    model[2]->insertRecord(0,record);
    model[2]->submitAll();
    model[2]->select();
}
