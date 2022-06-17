#ifndef SQL_H
#define SQL_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QString>
#include <QWidget>
#include <vector>
class sql
{
    void basic_setting();
public:
    QSqlDatabase database;
    QSqlTableModel* model[3];
    sql(QWidget* parent);
    ~sql();
    QSqlDatabase& getDatabase();
    void insert_object(int num,QString s,QString com);
    void insert_video(QString s,int size,int time);
    void insert_computer(QString s);
    auto do_sql(QString s)->std::vector<std::vector<QVariant>>;
};

#endif // SQL_H
