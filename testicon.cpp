#include "testicon.h"
#include "ui_testicon.h"

testicon::testicon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::testicon),
    _hidden(true)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);
    ui->frame->setStyleSheet("background : rgb(250, 250, 250);");
    this->resize(36,26);
}

testicon::~testicon()
{
    delete ui;
}

void testicon::add_mainwindow(QWidget *w)
{
    ui->verticalLayout_2->addWidget(w);
    _ptr = w;
    _ptr->setHidden(_hidden);
}

void testicon::on_pushButton_clicked()
{
    _hidden = !_hidden;
    _ptr->setHidden(_hidden);
    if(_hidden){
        this->resize(36,26);
    }else{
        this->resize(400,400);
    }
}
