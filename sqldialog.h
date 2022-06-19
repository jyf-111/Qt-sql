#ifndef SQLDIALOG_H
#define SQLDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCloseEvent>
#include "sql.h"

class SqlDialog:public QDialog
{
    Q_OBJECT
    sql* sql;
    std::unique_ptr<QTextEdit> textedit;
    std::unique_ptr<QLineEdit> lineedit;
    std::unique_ptr<QVBoxLayout> vlayout;
    void basic_setting();
    void set_layout();
    void set_connect();
public:
    std::unique_ptr<QPushButton> btn;
    SqlDialog(QWidget* parent);
};

#endif // SQLDIALOG_H
