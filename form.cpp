#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    AdvancedToolBox(parent),
    ui(new Ui::Form),
    _show(false),
    _first(true),
    _adjustsize(true)
{
    ui->setupUi(this);

    setWindowFlags(Qt::SubWindow);
//    setWindowModality(Qt::NonModal);

    this->load();
//    QString apppath = QCoreApplication::applicationDirPath();
//    QString configfile = apppath + "/config/gomihaco_config.json";

//    jsonioctrl::instance().readconfig(configfile);

//    auto ss = jsonioctrl::instance()._vecpages;
//    for(auto it = ss.begin();it != ss.end();++it)
//    {
////        qDebug() << it->index;
////        qDebug() << it->pagename;
//        QFrame* frame = new QFrame(this);
//        QVBoxLayout* l = new QVBoxLayout(frame);
//        auto cc =  it->veccontents;
//        for(auto itt = cc.begin();itt != cc.end();++itt)
//        {
////            qDebug() << itt->dispname;
////            qDebug() << itt->exepath;
//            QString path = itt->exepath;
//            QString execpath = "";
//            if(itt->sss == 0)
//                execpath = apppath + path;
//            else
//                execpath = path;
//            QPushButton* btn = new QPushButton(itt->dispname);
//            QObject::connect(btn,&QPushButton::clicked,[btn,/*path,apppath*/execpath,this](){
////                if(_mapprocess.contains(btn))
////                {
////                    QProcess* fork = _mapprocess.value(btn);
////                    qint64 processid = fork->processId();
////                    system(tr("kill -10 %1").arg(processid).toStdString().c_str());
////                }
////                else
////                {
//                    QProcess* fork = new QProcess;
////                    QString execpath = apppath + path;
//                    QFileInfo fileinfo(execpath);
//                    QString workpath = fileinfo.absolutePath();
////                    qDebug() << workpath;
////                    qDebug() << execpath;
//                    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
//                    fork->setWorkingDirectory(workpath);
//                    fork->setProgram(execpath);
//                    fork->setProcessEnvironment(env);
//                    fork->start();
////                    _mapprocess.insert(btn,fork);
////                }
//            });
//            l->addWidget(btn);
//        }
//        this->addWidget(frame,it->pagename);
//    }
}

Form::~Form()
{
    delete ui;
}

void Form::load()
{
    QString apppath = QCoreApplication::applicationDirPath();
    QString configfile = apppath + "/config/gomihaco_config.json";

    jsonioctrl::instance().readconfig(configfile);

    auto ss = jsonioctrl::instance()._vecpages;
    for(auto it = ss.begin();it != ss.end();++it)
    {
//        qDebug() << it->index;
//        qDebug() << it->pagename;
        QFrame* frame = new QFrame(this);
        QVBoxLayout* l = new QVBoxLayout(frame);
        auto cc =  it->veccontents;
        for(auto itt = cc.begin();itt != cc.end();++itt)
        {
//            qDebug() << itt->dispname;
//            qDebug() << itt->exepath;
            QString path = itt->exepath;
            QString execpath = "";
            if(itt->sss == 0)
                execpath = apppath + path;
            else
                execpath = path;
            QPushButton* btn = new QPushButton(itt->dispname);
            QObject::connect(btn,&QPushButton::clicked,[btn,/*path,apppath*/execpath,this](){
//                if(_mapprocess.contains(btn))
//                {
//                    QProcess* fork = _mapprocess.value(btn);
//                    qint64 processid = fork->processId();
//                    system(tr("kill -10 %1").arg(processid).toStdString().c_str());
//                }
//                else
//                {
                    QProcess* fork = new QProcess;
//                    QString execpath = apppath + path;
                    QFileInfo fileinfo(execpath);
                    QString workpath = fileinfo.absolutePath();
//                    qDebug() << workpath;
//                    qDebug() << execpath;
                    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
                    fork->setWorkingDirectory(workpath);
                    fork->setProgram(execpath);
                    fork->setProcessEnvironment(env);
                    fork->start();
//                    _mapprocess.insert(btn,fork);
//                }
            });
            l->addWidget(btn);
        }
        this->addWidget(frame,it->pagename);
    }
}

void Form::slot_doubleclick_show(QPoint pos)
{
    if(!_show)
    {
        this->show();
        this->showNormal();
        this->activateWindow();
        if(_adjustsize)
        {
            this->adjustsize();
            _adjustsize = false;
        }
        if(_first)
        {
            this->move(pos);
            _first = false;
        }
        else
        {
            this->move(_lastshown);
        }
    }
    else
    {
        _lastshown = this->pos();
        this->showMinimized();
    }
    _show = !_show;
}

void Form::slot_reload()
{
    for(int i = 0; i < this->getitemscount();i++)
    {
        this->setItemVisible(i,false);
    }
    _adjustsize = true;
    this->clear();
    this->load();
}

void Form::closeEvent(QCloseEvent *event)
{
    _show = false;
    _lastshown = this->pos();
    QWidget::closeEvent(event);
}
