#include "MyWidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent),
      // submodel new
      sql(new class sql),
      opencv(new class opencv),
      // widget new
      label(new QLabel),
      tabwidget(new QTabWidget),
      view{new QTableView, new QTableView, new QTableView},
      info_label(new QLabel("computer:")),
      // btn new
      vwritebtn(new QRadioButton("视频保存本地")),
      cameraOpenBtn(new QPushButton("camera")),
      fileOpenBtn(new QPushButton("open local viedo")),
      btn{new QPushButton("insert"), new QPushButton("delete"), new QPushButton("sql")},
      startbtn(new QPushButton("start")),
      stopbtn(new QPushButton("stop")),
      // layout new
      Hlayout(new QHBoxLayout(this)),
      rightVlayout(new QVBoxLayout),
      leftVlayout(new QVBoxLayout),

      rightbtnlayout(new QHBoxLayout),
      leftbtnlayout(new QHBoxLayout)
{
    //登录dialog
    class dialog : public QDialog
    {
    public:
        std::unique_ptr<QLabel> label;
        std::unique_ptr<QLineEdit> lineedit;
        std::unique_ptr<QPushButton> btn;
        std::unique_ptr<QVBoxLayout> vlayout;
        dialog(QWidget *parent = nullptr) : QDialog(parent),
                                            label(new QLabel),
                                            lineedit(new QLineEdit),
                                            btn(new QPushButton("login")),
                                            vlayout(new QVBoxLayout(this))
        {
            resize(200, 200);
            setWindowFlag(Qt::FramelessWindowHint);
            label->setFont(QFont("微软雅黑", 20));
            label->setText("登录");
            lineedit->setFont(QFont("Timer", 20));
            vlayout->addWidget(label.get(), 1, Qt::AlignCenter);
            vlayout->addWidget(lineedit.get());
            vlayout->addWidget(btn.get());
        }
    } dia(this);
    dia.setWindowTitle("computer");
    connect(dia.btn.get(), &QPushButton::clicked, [&]()
            {
        int count = sql->model[1]->rowCount();
        QSqlRecord record;
        bool login = false;
        for(int i=0;i<count;i++){
            record = sql->model[1]->record(i);
            if(record.value(0).toString()==dia.lineedit->text()){
                login = true;
                break;
            }
        }
        if(!login){
            QMessageBox::warning(this,"login","login deny");
            exit(0);
        }

        auto text = dia.lineedit->text();
        info_label->setText(text);
        dia.lineedit->clear();
        dia.close(); });
    dia.exec();

    set_basic_setting();
    set_layout();
    set_connect();
}

void MyWidget::set_basic_setting()
{
    setGeometry(25, 100, 1960 / 2, 1080 / 2);
    label->setAlignment(Qt::AlignCenter);
    label->setFont(QFont("Timer", 30));
    label->setText("监控管理系统");

    view[0]->setModel(sql->model[0]);
    view[1]->setModel(sql->model[1]);
    view[2]->setModel(sql->model[2]);
    for(int i=0;i<3;i++){
        view[i]->setModel(sql->model[i]);
    }

    tabwidget->addTab(view[0], "object");
    tabwidget->addTab(view[1], "computer");
    tabwidget->addTab(view[2], "video");
    tabwidget->setStyleSheet("QTabBar::tab{width:125px}");
}

void MyWidget::set_layout()
{
    // right
    rightVlayout->addWidget(info_label.get());
    rightVlayout->addWidget(tabwidget.get());

    rightbtnlayout->addWidget(vwritebtn.get());
    rightbtnlayout->addWidget(fileOpenBtn.get());
    rightbtnlayout->addWidget(cameraOpenBtn.get());
    rightbtnlayout->addWidget(btn[0]);
    rightbtnlayout->addWidget(btn[1]);
    rightbtnlayout->addWidget(btn[2]);
    rightVlayout->addLayout(rightbtnlayout.get());

    leftbtnlayout->addWidget(startbtn.get());
    leftbtnlayout->addWidget(stopbtn.get());

    leftVlayout->addWidget(label.get());
    leftVlayout->addLayout(leftbtnlayout.get());
    leftVlayout->setStretch(0, 5);
    leftVlayout->setStretch(1, 1);

    Hlayout->addLayout(leftVlayout.get());
    Hlayout->addLayout(rightVlayout.get());
    Hlayout->setStretchFactor(leftVlayout.get(), 5);
    Hlayout->setStretchFactor(rightVlayout.get(), 1);
}

MyWidget::~MyWidget()
{
    delete[] & view;
    delete[] & btn;
}

void MyWidget::set_connect()
{
    connect(startbtn.get(), &QPushButton::clicked, [this]()
            { opencv->qtimer->start(); });

    connect(stopbtn.get(), &QPushButton::clicked, [this]()
            { opencv->qtimer->stop(); });

    connect(opencv->qtimer.get(), &QTimer::timeout, [this]()
            {
        if(opencv->dispose()){
            label->setPixmap(QPixmap::fromImage(opencv->get_result()));
            auto tmp = opencv->get_tips();
            sql->database.transaction();
            sql->do_sql("delete from object");
            int num = tmp.size();
            for(int i=0;i<num;i++){
                sql->insert_object(i,tmp[i],info_label->text());
            }
            sql->database.commit();
        } });

    connect(btn[0], &QPushButton::clicked, [this]()
            {
        auto mod = sql->model[tabwidget->currentIndex()];
        mod->insertRows(0,1); });

    connect(btn[1], &QPushButton::clicked, [this]()
            {
        auto num = tabwidget->currentIndex();
        int row = view[num]->currentIndex().row();
        if(QMessageBox::Yes == QMessageBox::question(this,"Make Sure","确定删除第"+QString::number(row+1)+"行吗？",QMessageBox::Yes | QMessageBox::No , QMessageBox::Yes))
            {
            sql->model[num]->removeRow(row);
            sql->model[num]->select();
        } });

    connect(btn[2], &QPushButton::clicked, [this]()
            {
        std::unique_ptr<SqlDialog> sqlDialog(new SqlDialog(this));
        connect(sqlDialog->btn.get(),&QPushButton::clicked,[this](){
            qDebug() << "in button";
            //            flush
            for(int i=0;i<3;i++)
                sql->model[i]->select();
        });
        sqlDialog->exec(); });

    connect(fileOpenBtn.get(), &QPushButton::clicked, [=]()
            {
        QString path = QFileDialog::getOpenFileName(this, "video", "./Videos", "video(*.avi *.mp4 *.flv)");
        if (!path.isEmpty()){
            opencv->set_video(path);
            sql->insert_video(path, opencv->videoInfo.width, opencv->videoInfo.height, info_label->text());
        } });

    connect(cameraOpenBtn.get(), &QPushButton::clicked, [this]()
            {
        class Dialog : public QDialog
        {
        public:
            std::unique_ptr<QLineEdit> lineedit{new QLineEdit(this)};
            std::unique_ptr<QPushButton> btn{new QPushButton("ok", this)};
            std::unique_ptr<QHBoxLayout> hLayout{new QHBoxLayout(this)};
            Dialog()
            {
                resize(400, 50);
                setWindowTitle("camera");
                lineedit->setFont(QFont("Timer", 16));
                hLayout->addWidget(lineedit.get());
                hLayout->addWidget(btn.get());
            }
        } dialog;
        connect(dialog.btn.get(), &QPushButton::clicked, [&dialog, this]()
                {
            opencv->set_video(dialog.lineedit->text());
            dialog.close(); });
        dialog.exec(); });

    connect(vwritebtn.get(), &QRadioButton::toggled, [this]()
            {
        if (vwritebtn->isChecked())
        {
            opencv->do_writer = true;
        }
        else
        {
            opencv->do_writer = false;
        } });
}
