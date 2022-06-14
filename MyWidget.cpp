#include "MyWidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent),
      le(new QLineEdit(this)),
      te(new QTextEdit(this)),
      btn(new QPushButton("exec", this))
{
    resize(800, 600);
    le->setGeometry(50, 400, 700, 50);
    le->show();
    te->setGeometry(50, 30, 700, 300);
    te->show();
    QObject::connect(btn, &QPushButton::clicked,this,&MyWidget::do_query);
    btn->setGeometry(350, 480, 100, 40);
    btn->show();

    connect_sqlite();
}

MyWidget::~MyWidget()
{
    database.close();
}

void MyWidget::connect_sqlite()
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

void MyWidget::do_query()
{
    QString s(qPrintable(le->text()));
    QSqlQuery query(database);
    query.exec(s);
    te->append("> " + s);
    while (query.next())
    {
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        QString sex = query.value(2).toString();
        qDebug() << QString("id:%1    name:%2    sex:%3").arg(id).arg(name).arg(sex);
        te->append(QString("id:%1    name:%2    sex:%3").arg(id).arg(name).arg(sex));
    }
    te->append("-------------------");
}

void MyWidget::opencv(){
    cv::VideoCapture cap(0);
    cv::Mat frame;
    while (1)
    {
        cap >> frame;
        cv::imshow("video", frame);
        if(cv::waitKey(30) == 27) break;
    }
    cv::destroyAllWindows();
}
