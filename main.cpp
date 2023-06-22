#include <QApplication>
//#include "mainwindow.h"
#include "form.h"
//#include "testicon.h"
#include "config.h"
#include "calcultor.h"
#include "framelesswidget.h"
#if 0
#include "advancedtoolbox.h"
#include <QFrame>
#include <QPushButton>
#include <QDebug>
#include <QToolBar>
#include <QObject>
#include <QVBoxLayout>
#include <QProcess>
#include "jsonioctrl.hpp"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    MainWindow* w = new MainWindow;
//    w->show();
    FramelessWidget* fw = new FramelessWidget;
    fw->setFixedSize(60,60);
//    fw->setStyleSheet("border-image: url(:/globe_color_48.png);");
    QString iconfile = QCoreApplication::applicationDirPath() + "/icon.png";
    QFile file(iconfile);
    QPixmap icon;
    if(file.exists())
        icon = QPixmap(iconfile);
    else
        icon = QPixmap(":/icon.png");
    icon = icon.scaled(60,60);
    fw->setPixmap(icon);
    fw->show();

    Form* f = new Form;
    f->setWindowTitle("contents");
    QObject::connect(fw,&FramelessWidget::sig_doubleclicked,f,&Form::slot_doubleclick_show);
    QObject::connect(fw,&FramelessWidget::sig_exit,f,&Form::close);
    QObject::connect(fw,&FramelessWidget::sig_reload,f,&Form::slot_reload);

    config* c = new config;
    c->setWindowTitle("config");
    QObject::connect(fw,&FramelessWidget::sig_config,c,&config::show);
    QObject::connect(fw,&FramelessWidget::sig_exit,c,&config::close);
    QObject::connect(fw,&FramelessWidget::sig_reload,c,&config::reload);

    calcultor* _calcultor = new calcultor;
    _calcultor->setWindowTitle("_calcultor");
    QObject::connect(fw,&FramelessWidget::sig_calcultor,_calcultor,&calcultor::show);
    QObject::connect(fw,&FramelessWidget::sig_exit,_calcultor,&calcultor::close);

    QObject::connect(fw,&FramelessWidget::sig_exit,[&](){
        fw->deleteLater();
        c->deleteLater();
        f->deleteLater();
        _calcultor->deleteLater();
        a.quit();
    });

//    testicon* icon = new testicon;
//    icon->add_mainwindow(f);
//    icon->show();
#if 0
    AdvancedToolBox* w = new AdvancedToolBox(0);

    QString apppath = QCoreApplication::applicationDirPath();
    QString configfile = apppath + "/config/gomihaco_config.json";

    jsonioctrl::instance().readconfig(configfile);

    auto ss = jsonioctrl::instance()._vecpages;
    for(auto it = ss.begin();it != ss.end();++it)
    {
        qDebug() << it->index;
        qDebug() << it->pagename;
        QFrame* frame = new QFrame(w);
        QVBoxLayout* l = new QVBoxLayout(frame);
        auto cc =  it->veccontents;
        for(auto itt = cc.begin();itt != cc.end();++itt)
        {
            qDebug() << itt->dispname;
            qDebug() << itt->exepath;
            QString path = itt->exepath;
            QPushButton* btn = new QPushButton(itt->dispname);
            QObject::connect(btn,&QPushButton::clicked,[btn,path,apppath](){
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
            });
            l->addWidget(btn);
        }
        w->addWidget(frame,it->pagename);
    }

//    AdvancedToolBox* w = new AdvancedToolBox(0);
//    QFrame* frame = new QFrame(w);

//    frame->setStyleSheet("QFrame{background:#E8BD92;}");
//    frame->setMaximumHeight(300);
//    w->addWidget(frame,"AAA");

//    frame = new QFrame(w);
//    frame->setStyleSheet("QFrame{background:#BDE8A7;}");
//    w->addWidget(frame,"BBB");

//    QWidget* btn = new QPushButton("abc", w);
//    btn->setStyleSheet("QFrame{background:#78B294;}");
//    w->addWidget(btn,"CCC");

    w->show();
#endif
    return a.exec();
}
