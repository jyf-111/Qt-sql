#ifndef SQL_H
#define SQL_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
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
    void insert_object(int num,QString s,QString cname);
    void insert_computer(QString s);
    void insert_video(QString s,int width,int height,QString cname);
    auto do_sql(QString s)->std::vector<std::vector<QVariant>>;
};

#endif // SQL_H
