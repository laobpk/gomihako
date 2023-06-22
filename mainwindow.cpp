#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString apppath = QCoreApplication::applicationDirPath();
    QString configfile = apppath + "/config/gomihaco_config.json";

    jsonioctrl::instance().readconfig(configfile);

    auto ss = jsonioctrl::instance()._vecpages;
    for(auto it = ss.begin();it != ss.end();++it)
    {
        qDebug() << it->index;
        qDebug() << it->pagename;
        QFrame* frame = new QFrame(ui->centralwidget);
        QVBoxLayout* l = new QVBoxLayout(frame);
        auto cc =  it->veccontents;
        for(auto itt = cc.begin();itt != cc.end();++itt)
        {
            qDebug() << itt->dispname;
            qDebug() << itt->exepath;
            QString path = itt->exepath;
            QPushButton* btn = new QPushButton(itt->dispname);
            QObject::connect(btn,&QPushButton::clicked,[btn,path,apppath,this](){
                if(_mapprocess.contains(btn))
                {
//                    QProcess* fork = _mapprocess.value(btn);
//                    qint64 processid = fork->processId();
//                    system(tr("kill -10 %1").arg(processid).toStdString().c_str());
                }
                else
                {
                    QProcess* fork = new QProcess;
                    QString execpath = apppath + path;
                    QFileInfo fileinfo(execpath);
                    QString workpath = fileinfo.absolutePath();
                    qDebug() << workpath;
                    qDebug() << execpath;
                    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
                    fork->setWorkingDirectory(workpath);
                    fork->setProgram(execpath);
                    fork->setProcessEnvironment(env);
                    fork->start();
                    _mapprocess.insert(btn,fork);
                }
            });
            l->addWidget(btn);
        }
        ui->centralwidget->addWidget(frame,it->pagename);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
