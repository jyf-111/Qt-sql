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
}

sql::~sql(){
    database.close();
}

void sql::do_query()
{
//    QString s(qPrintable(le->text()));
    QSqlQuery query(database);
    if(!query.exec("select * from object")){
        qDebug() << "query fail";
        exit(0);
    }
//    te->append("> " + s);
    while (query.next())
    {
        QString name= query.value(0).toString();
        qint64 num= query.value(1).toInt();
        qDebug() << QString("name:%1    num:%2").arg(name).arg(num);
//        te->append(QString("id:%1    name:%2    sex:%3").arg(id).arg(name).arg(sex));
    }
//    te->append("-------------------");
}
