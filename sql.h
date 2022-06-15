#ifndef SQL_H
#define SQL_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>

class sql
{
public:
    QSqlDatabase database;
    sql();
    ~sql();
    void do_query();
};

#endif // SQL_H
