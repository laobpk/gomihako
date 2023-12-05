#include "player.h"
#include "ui_player.h"
#include <QDebug>

Player::Player(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Player),
    _resizeDir(Nodir),
    _edgeMargin(6),
    _dragtonormal(false),
    _tray_icon(new QSystemTrayIcon(this)),
    _tray_menu(new QMenu(this))
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setMouseTracking(true);

    _tray_icon->setIcon(QIcon(":/icon.png"));
    _tray_icon->setToolTip(tr("system tray icon test"));

    systemtraymenu();

    connect(_tray_icon,&QSystemTrayIcon::activated,this,[=](QSystemTrayIcon::ActivationReason reason){
        switch (reason) {
        case QSystemTrayIcon::Trigger:
            // click
            break;
        case QSystemTrayIcon::DoubleClick:
            this->show();
            break;
        case QSystemTrayIcon::Context:
            _tray_menu->show();
            break;
        default:
            break;
        }
    });

    _tray_icon->show();
}

Player::~Player()
{
    delete ui;
}

void Player::testEdge()
{
    if(this->isMaximized())
        return;
    int diffleft = abs(cursor().pos().x() - frameGeometry().left());
    int diffright = abs(cursor().pos().x() - frameGeometry().right());
    int difftop = abs(cursor().pos().y() - frameGeometry().top());
    int diffbottom = abs(cursor().pos().y() - frameGeometry().bottom());

    QCursor tempCursor = cursor();
    if(difftop < _edgeMargin)
    {
        if(diffleft < _edgeMargin)
        {
            _resizeDir = TopLeft;
            tempCursor.setShape(Qt::SizeFDiagCursor);
        }
        else if(diffright < _edgeMargin)
        {
            _resizeDir = TopRight;
            tempCursor.setShape(Qt::SizeBDiagCursor);
        }
        else
        {
            _resizeDir = Top;
            tempCursor.setShape(Qt::SizeVerCursor);
        }
    }
    else if(diffbottom < _edgeMargin)
    {
        if(diffleft < _edgeMargin)
        {
            _resizeDir = BottomLeft;
            tempCursor.setShape(Qt::SizeBDiagCursor);
        }
        else if(diffright < _edgeMargin)
        {
            _resizeDir = BottomRight;
            tempCursor.setShape(Qt::SizeFDiagCursor);
        }
        else
        {
            _resizeDir = Bottom;
            tempCursor.setShape(Qt::SizeVerCursor);
        }
    }
    else if (diffleft < _edgeMargin)
    {
        _resizeDir = Left;
        tempCursor.setShape(Qt::SizeHorCursor);
    }
    else if (diffright < _edgeMargin)
    {
        _resizeDir = Right;
        tempCursor.setShape(Qt::SizeHorCursor);
    }
    else
    {
        _resizeDir = Nodir;
        tempCursor.setShape(Qt::ArrowCursor);
    }
    setCursor(tempCursor);
}

void Player::systemtraymenu()
{
    QAction* close = new QAction("close");
    connect(close,&QAction::triggered,this,[&](){
        this->close();
    });
    _tray_menu->addAction(close);
    _tray_icon->setContextMenu(_tray_menu);
}

void Player::mousePressEvent(QMouseEvent *event)
{
    if(this->isMaximized())
        _dragtonormal = true;
    if(event->button() == Qt::LeftButton)
    {
        testEdge();
        _dragPosition = event->globalPos() - this->frameGeometry().topLeft();
    }
}

void Player::mouseReleaseEvent(QMouseEvent *)
{
//    if(_resizeDir != Nodir)
    if(_dragtonormal)
        _dragtonormal = false;
    testEdge();
}

void Player::mouseMoveEvent(QMouseEvent *e)
{
//    e->ignore();
    if(_dragtonormal)
    {
        this->showNormal();
        _dragtonormal = false;
    }
    else
    {
        if(e->buttons() & Qt::LeftButton)
        {
            if(_resizeDir == Nodir)
            {
                if(this->isMaximized())
                    return;
                move(e->globalPos() - _dragPosition);
            }
            else
            {
                int ptop,pbottom,pleft,pright;
                ptop = frameGeometry().top();
                pbottom = frameGeometry().bottom();
                pleft = frameGeometry().left();
                pright = frameGeometry().right();
                if(_resizeDir & Top)
                {
                    if(height() == minimumHeight())
                        ptop = qMin(e->globalY(),ptop);
                    else if(height() == maximumHeight())
                        ptop = qMax(e->globalY(),ptop);
                    else
                        ptop = e->globalY();
                }
                else if (_resizeDir & Bottom)
                {
                    if(height() == minimumHeight())
                        pbottom = qMax(e->globalY(),ptop);
                    else if(height() == maximumHeight())
                        pbottom = qMin(e->globalY(),ptop);
                    else
                        pbottom = e->globalY();
                }
                if(_resizeDir & Left)
                {
                    if(width() == minimumWidth())
                        pleft = qMin(e->globalX(),pleft);
                    else if (width() == maximumWidth())
                        pleft = qMax(e->globalY(),pleft);
                    else
                        pleft = e->globalY();
                }
                else if (_resizeDir & Right)
                {
                    if(width() == minimumWidth())
                        pright = qMax(e->globalX(),pright);
                    else if (width() == maximumWidth())
                        pright = qMin(e->globalX(),pright);
                    else
                        pright = e->globalX();
                }
                setGeometry(QRect(QPoint(pleft,ptop),QPoint(pright,pbottom)));
            }
        }
        else{
            testEdge();
        }
    }
}

void Player::keyPressEvent(QKeyEvent *event)
{
    qDebug() << event->key();
}

void Player::on_toolButton_clicked()
{
    this->hide();
}

