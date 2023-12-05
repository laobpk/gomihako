#include "config.h"
#include "ui_config.h"

config::config(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::config)
{
    ui->setupUi(this);

    setWindowFlags(Qt::SubWindow);
//    setWindowModality(Qt::NonModal);

    this->readconfig();
    ui->btn_saveone->setWhatsThis("");
}

config::~config()
{
    delete ui;
}

void config::reload()
{
    ui->treeWidget->clear();
    QString apppath = QCoreApplication::applicationDirPath();
    auto ss = jsonioctrl::instance()._vecpages;
    for(auto it = ss.begin();it != ss.end();++it)
    {
        int pageindex = it->index;
        QString pagename = it->pagename;
        QTreeWidgetItem* root = new QTreeWidgetItem();
        root->setText(0,pagename);
        root->setData(0,Qt::UserRole,QVariant("root"));
        root->setData(1,Qt::UserRole,QVariant(pageindex));
        ui->treeWidget->addTopLevelItem(root);
        auto cc =  it->veccontents;
        for(auto itt = cc.begin();itt != cc.end();++itt)
        {
            QString path = itt->exepath;
            QString execpath = "";
            if(itt->sss == 0)
                execpath = apppath + path;
            else
                execpath = path;
            QString dispname = itt->dispname;
            QTreeWidgetItem* child = new QTreeWidgetItem();
            child->setText(0,dispname);
            child->setData(0,Qt::UserRole,QVariant("child"));
            child->setData(1,Qt::UserRole,QVariant(itt->sss));
            child->setData(2,Qt::UserRole,QVariant(execpath));
            child->setData(3,Qt::UserRole,QVariant(itt->id));
            root->addChild(child);
        }
    }
}

void config::readconfig()
{
    QString apppath = QCoreApplication::applicationDirPath();
    QString configfile = apppath + "/config/gomihaco_config.json";

    jsonioctrl::instance().readconfig(configfile);

    this->reload();
}

void config::on_btn_saveone_clicked()
{
    QString id = ui->btn_saveone->whatsThis();
    if(id == "")
        return;
    QString apppath = QCoreApplication::applicationDirPath();
//    int pageindex = ui->le_dispname->whatsThis().toInt();
    QString dispname = ui->le_dispname->text().trimmed();
    int pathtype = ui->cb_pathtype->currentIndex();
    QString execpath = ui->le_execpath->text().trimmed();
    if (pathtype == 0)
    {
        execpath = execpath.remove(apppath);
    }

    for (int i = 0; i < jsonioctrl::instance()._vecpages.count() ;i++)
    {
//        if (jsonioctrl::instance()._vecpages.at(i).index == pageindex)
//        {
            for (int j = 0; j < jsonioctrl::instance()._vecpages.at(i).veccontents.count() ; j++)
            {
                if (jsonioctrl::instance()._vecpages.at(i).veccontents.at(j).id == id)
                {
                    jsonioctrl::instance()._vecpages[i].veccontents[j].dispname = dispname;
                    jsonioctrl::instance()._vecpages[i].veccontents[j].sss = pathtype;
                    jsonioctrl::instance()._vecpages[i].veccontents[j].exepath = execpath;
                }
            }
//        }
    }
}

void config::on_btn_saveall_clicked()
{
    QString apppath = QCoreApplication::applicationDirPath();
    QString configfile = apppath + "/config/gomihaco_config.json";

    jsonioctrl::instance().writeconfig(configfile);
}

void config::on_btn_page_clicked()
{
    int index = ui->btn_page->whatsThis().toInt();
    QString pagename = ui->le_pagename->text().trimmed();

    for(int i = 0; i < jsonioctrl::instance()._vecpages.count() ;i++)
    {
        if (jsonioctrl::instance()._vecpages.at(i).index == index)
            jsonioctrl::instance()._vecpages[i].pagename = pagename;
    }
}

void config::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    QString type = item->data(0,Qt::UserRole).toString();
    if(type == "root")
    {
        ui->le_pagename->setText(item->text(0));
        ui->btn_page->setWhatsThis(QString::number(item->data(1,Qt::UserRole).toInt()));
    }
    if(type == "child")
    {
        ui->le_pagename->setText(item->parent()->text(0));
        ui->cb_pathtype->setCurrentIndex(item->data(1,Qt::UserRole).toInt());
        ui->le_execpath->setText(item->data(2,Qt::UserRole).toString());
        ui->le_dispname->setText(item->text(0));
        ui->le_dispname->setWhatsThis(QString::number(item->parent()->data(1,Qt::UserRole).toInt()));
        ui->btn_saveone->setWhatsThis(item->data(3,Qt::UserRole).toString());
    }
}

void config::on_actionadd_program_triggered()
{
//    QFileDialog* aa = new QFileDialog(this,Qt::ForeignWindow);
//    aa->setWindowModality(Qt::NonModal);
//    QString filename = aa->getOpenFileName(0,tr("open file"),
    QString filename = QFileDialog::getOpenFileName(this,tr("open file"),
                                 "/root",
                                 tr("executions (*.*);;shell (*.sh)"));
    if(filename == "")
    {
        return;
    }
    QString id = QDateTime::currentDateTime().toString("yyMMddhhmmsszzz");
    QString dispname = "new program";
    int pageindex = 0;
    ui->treeWidget->blockSignals(true);
    QTreeWidgetItem* child = new QTreeWidgetItem();
    child->setText(0,dispname);
    child->setData(0,Qt::UserRole,QVariant("child"));
    child->setData(1,Qt::UserRole,QVariant(1));
    child->setData(2,Qt::UserRole,QVariant(filename));
    child->setData(3,Qt::UserRole,QVariant(id));
    if(ui->treeWidget->currentItem()->data(0,Qt::UserRole).toString() == "root")
    {
        pageindex = ui->treeWidget->currentItem()->data(1,Qt::UserRole).toInt();
        ui->treeWidget->currentItem()->addChild(child);

//        ui->le_pagename->setText(ui->treeWidget->currentItem()->text(0));
//        ui->btn_page->setWhatsThis(QString::number(pageindex));
    }
    if(ui->treeWidget->currentItem()->data(0,Qt::UserRole).toString() == "child")
    {
        pageindex = ui->treeWidget->currentItem()->parent()->data(1,Qt::UserRole).toInt();
        ui->treeWidget->currentItem()->parent()->addChild(child);

//        ui->le_pagename->setText(ui->treeWidget->currentItem()->parent()->text(0));
//        ui->cb_pathtype->setCurrentIndex(ui->treeWidget->currentItem()->data(1,Qt::UserRole).toInt());
//        ui->le_execpath->setText(ui->treeWidget->currentItem()->data(2,Qt::UserRole).toString());
//        ui->le_dispname->setText(ui->treeWidget->currentItem()->text(0));
//        ui->le_dispname->setWhatsThis(QString::number(ui->treeWidget->currentItem()->parent()->data(1,Qt::UserRole).toInt()));
//        ui->btn_saveone->setWhatsThis(ui->treeWidget->currentItem()->data(3,Qt::UserRole).toString());
    }
    for (int i = 0; i < jsonioctrl::instance()._vecpages.count() ;i++)
    {
        if (jsonioctrl::instance()._vecpages.at(i).index == pageindex)
        {
            program newprogram;
            newprogram.id = id;
            newprogram.dispname = dispname;
            newprogram.exepath = filename;
            newprogram.sss = 1;
            jsonioctrl::instance()._vecpages[i].veccontents.push_back(newprogram);
        }
    }
    ui->treeWidget->blockSignals(false);
    on_treeWidget_itemClicked(child, 0);
//    if(type == "root")
//    {
//        ui->le_pagename->setText(item->text(0));
//        ui->btn_page->setWhatsThis(QString::number(item->data(1,Qt::UserRole).toInt()));
//    }
//    if(type == "child")
//    {
//        ui->le_pagename->setText(item->parent()->text(0));
//        ui->cb_pathtype->setCurrentIndex(item->data(1,Qt::UserRole).toInt());
//        ui->le_execpath->setText(item->data(2,Qt::UserRole).toString());
//        ui->le_dispname->setText(item->text(0));
//        ui->le_dispname->setWhatsThis(QString::number(item->parent()->data(1,Qt::UserRole).toInt()));
//        ui->btn_saveone->setWhatsThis(item->data(3,Qt::UserRole).toString());
//    }
}

void config::on_actionadd_page_triggered()
{
    ui->treeWidget->blockSignals(true);
    int index = 1;
    for(int i = 0; i < jsonioctrl::instance()._vecpages.count() ;i++)
    {
        if (jsonioctrl::instance()._vecpages.at(i).index > index)
            index = jsonioctrl::instance()._vecpages.at(i).index + 1;
    }
    page newpage;
    newpage.index = index;
    newpage.pagename = "new page";
    jsonioctrl::instance()._vecpages.push_back(newpage);
    QTreeWidgetItem* newroot = new QTreeWidgetItem();
    newroot->setText(0,"new page");
    newroot->setData(0,Qt::UserRole,QVariant("root"));
    newroot->setData(1,Qt::UserRole,QVariant(index));
    ui->treeWidget->addTopLevelItem(newroot);
    ui->treeWidget->blockSignals(false);
    on_treeWidget_itemClicked(newroot, 0);
}


void config::on_actionenglish_triggered()
{
    jsonioctrl::instance()._language = language::english;
    emit sig_switchlanguage();
}


void config::on_actionchinese_triggered()
{
    jsonioctrl::instance()._language = language::chinese;
    emit sig_switchlanguage();
}


void config::on_actionrussian_triggered()
{
    jsonioctrl::instance()._language = language::russian;
}


void config::on_actionfrench_triggered()
{
    jsonioctrl::instance()._language = language::french;
    emit sig_switchlanguage();
}


void config::on_actionjapanese_triggered()
{
    jsonioctrl::instance()._language = language::japanese;
    emit sig_switchlanguage();
}


void config::on_actionkorean_triggered()
{
    jsonioctrl::instance()._language = language::korean;
    emit sig_switchlanguage();
}


void config::on_actiongerman_triggered()
{
    jsonioctrl::instance()._language = language::german;
    emit sig_switchlanguage();
}

