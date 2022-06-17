#ifndef SQLDIALOG_H
#define SQLDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include "sql.h"

class SqlDialog:public QDialog
{
    sql* sql;
    QTextEdit* textedit;
    QLineEdit* lineedit;
    QPushButton* btn;
    QVBoxLayout* vlayout;
    void basic_setting();
    void set_layout();
    void set_connect();
public:
    SqlDialog();

};

#endif // SQLDIALOG_H
