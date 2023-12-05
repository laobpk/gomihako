#include "framelesswidget.h"
#include <QDebug>

FramelessWidget::FramelessWidget(QWidget *parent) :
    QLabel(parent),
    _contextmenu(new QMenu(this)) //,
//    _edgeMargin(6),
//    _resizeDir(Nodir),
//    _dragtonormal(false)
{
    this->setWindowFlags(Qt::Tool/*Dialog*/|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
//    this->setWindowModality(Qt::NonModal);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_StyleSheet,true);
    this->setMouseTracking(true);
    this->setFocusPolicy(Qt::StrongFocus);

    QString apppath = QCoreApplication::applicationDirPath();
    QString configfile = apppath + "/config/gomihaco_config.json";
    jsonioctrl::instance().readconfig(configfile);


//    QAction* terminal = new QAction("terminal",this);
//    connect( terminal , &QAction::triggered , this , [&](){
////        system("bash");
//        QProcess::startDetached("gnome-terminal");
//    } );
//    _contextmenu->addAction(terminal);

    QAction* editor = new QAction(tr("editor"),this);
    connect( editor , &QAction::triggered , this , [&](){
        QString filename = QFileDialog::getOpenFileName(this,tr("open file"),
                                                        jsonioctrl::instance()._default_editor_path,
                                                        tr("allfile (*);;files (*.txt *.xml *.ini);;shell (*.sh)"));
        if(filename == "")
            return;
        QFileInfo file(filename);
        jsonioctrl::instance()._default_editor_path = file.filePath();
        QString command = QString("pluma %1").arg(filename);
//        system(command.toStdString().c_str());
        QProcess pro;
        pro.startDetached(command.toStdString().c_str());
    } );
//    editor->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
    _contextmenu->addAction(editor);

    QAction* calcultor = new QAction(tr("calcultor"),this);
    connect( calcultor , &QAction::triggered , this , [&](){
        emit sig_calcultor();
    } );
//    reload->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    _contextmenu->addAction(calcultor);

    QAction* reload = new QAction(tr("reload"),this);
    connect( reload , &QAction::triggered , this , [&](){
        emit sig_reload();
    } );
//    reload->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    _contextmenu->addAction(reload);

    QAction* config = new QAction(tr("settings"),this);
    connect( config , &QAction::triggered , this , [&](){
        emit sig_config();
    } );
//    config->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    _contextmenu->addAction(config);

    QAction* close = new QAction(tr("close"),this);
    connect( close , &QAction::triggered , this , [&](){
        QString apppath = QCoreApplication::applicationDirPath();
        QString configfile = apppath + "/config/gomihaco_config.json";
        jsonioctrl::instance().writeconfig(configfile);
        emit sig_exit();
        this->close();
    } );
//    close->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    _contextmenu->addAction(close);
}

FramelessWidget::~FramelessWidget()
{
}

//void FramelessWidget::testEdge()
//{
//    if(this->isMaximized())
//        return;
//    int diffleft = abs(cursor().pos().x() - frameGeometry().left());
//    int diffright = abs(cursor().pos().x() - frameGeometry().right());
//    int difftop = abs(cursor().pos().y() - frameGeometry().top());
//    int diffbottom = abs(cursor().pos().y() - frameGeometry().bottom());

//    QCursor tempCursor = cursor();
//    if(difftop < _edgeMargin)
//    {
//        if(diffleft < _edgeMargin)
//        {
//            _resizeDir = TopLeft;
//            tempCursor.setShape(Qt::SizeFDiagCursor);
//        }
//        else if(diffright < _edgeMargin)
//        {
//            _resizeDir = TopRight;
//            tempCursor.setShape(Qt::SizeBDiagCursor);
//        }
//        else
//        {
//            _resizeDir = Top;
//            tempCursor.setShape(Qt::SizeVerCursor);
//        }
//    }
//    else if(diffbottom < _edgeMargin)
//    {
//        if(diffleft < _edgeMargin)
//        {
//            _resizeDir = BottomLeft;
//            tempCursor.setShape(Qt::SizeBDiagCursor);
//        }
//        else if(diffright < _edgeMargin)
//        {
//            _resizeDir = BottomRight;
//            tempCursor.setShape(Qt::SizeFDiagCursor);
//        }
//        else
//        {
//            _resizeDir = Bottom;
//            tempCursor.setShape(Qt::SizeVerCursor);
//        }
//    }
//    else if (diffleft < _edgeMargin)
//    {
//        _resizeDir = Left;
//        tempCursor.setShape(Qt::SizeHorCursor);
//    }
//    else if (diffright < _edgeMargin)
//    {
//        _resizeDir = Right;
//        tempCursor.setShape(Qt::SizeHorCursor);
//    }
//    else
//    {
//        _resizeDir = Nodir;
//        tempCursor.setShape(Qt::ArrowCursor);
//    }
//    setCursor(tempCursor);
//}

void FramelessWidget::mousePressEvent(QMouseEvent *e)
{
//    if(this->isMaximized())
//        _dragtonormal = true;
    if(e->button() == Qt::LeftButton)
    {
//        testEdge();
        _dragPosition = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void FramelessWidget::mouseReleaseEvent(QMouseEvent *e)
{
////    if(_resizeDir != Nodir)
//    if(_dragtonormal)
//        _dragtonormal = false;
//    testEdge();
}

void FramelessWidget::mouseMoveEvent(QMouseEvent *e)
{
////    e->ignore();
//    if(_dragtonormal)
//    {
//        this->showNormal();
//        _dragtonormal = false;
//    }
//    else
//    {
        if(e->buttons() & Qt::LeftButton)
        {
//            if(_resizeDir == Nodir)
//            {
                if(this->isMaximized())
                    return;
                move(e->globalPos() - _dragPosition);
//            }
//            else
//            {
//                int ptop,pbottom,pleft,pright;
//                ptop = frameGeometry().top();
//                pbottom = frameGeometry().bottom();
//                pleft = frameGeometry().left();
//                pright = frameGeometry().right();
//                if(_resizeDir & Top)
//                {
//                    if(height() == minimumHeight())
//                        ptop = qMin(e->globalY(),ptop);
//                    else if(height() == maximumHeight())
//                        ptop = qMax(e->globalY(),ptop);
//                    else
//                        ptop = e->globalY();
//                }
//                else if (_resizeDir & Bottom)
//                {
//                    if(height() == minimumHeight())
//                        pbottom = qMax(e->globalY(),ptop);
//                    else if(height() == maximumHeight())
//                        pbottom = qMin(e->globalY(),ptop);
//                    else
//                        pbottom = e->globalY();
//                }
//                if(_resizeDir & Left)
//                {
//                    if(width() == minimumWidth())
//                        pleft = qMin(e->globalX(),pleft);
//                    else if (width() == maximumWidth())
//                        pleft = qMax(e->globalY(),pleft);
//                    else
//                        pleft = e->globalY();
//                }
//                else if (_resizeDir & Right)
//                {
//                    if(width() == minimumWidth())
//                        pright = qMax(e->globalX(),pright);
//                    else if (width() == maximumWidth())
//                        pright = qMin(e->globalX(),pright);
//                    else
//                        pright = e->globalX();
//                }
//                setGeometry(QRect(QPoint(pleft,ptop),QPoint(pright,pbottom)));
//            }
        }
//        else{
//            testEdge();
//        }
//    }
}

void FramelessWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
//    if(this->isMaximized())
//        this->showNormal();
//    else
//        this->showMaximized();
    emit sig_doubleclicked(event->globalPos());
}

void FramelessWidget::contextMenuEvent(QContextMenuEvent *event)
{
    _contextmenu->exec(event->globalPos());
}

void FramelessWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier)
    {
        if (event->key() == Qt::Key_Q)
        {
            QString apppath = QCoreApplication::applicationDirPath();
            QString configfile = apppath + "/config/gomihaco_config.json";
            jsonioctrl::instance().writeconfig(configfile);
            emit sig_exit();
            this->close();
        }
        else if (event->key() == Qt::Key_E)
        {
            QString filename = QFileDialog::getOpenFileName(this,tr("open file"),
                                                            jsonioctrl::instance()._default_editor_path,
                                                            tr("allfile (*);;files (*.txt *.xml *.ini);;shell (*.sh)"));
            if(filename == "")
                return;
            QFileInfo file(filename);
            jsonioctrl::instance()._default_editor_path = file.filePath();
            QString command = QString("pluma %1").arg(filename);
//            system(command.toStdString().c_str());
            QProcess pro;
            pro.startDetached(command.toStdString().c_str());
        }
        else if (event->key() == Qt::Key_O)
        {
            emit sig_config();
        }
        else if (event->key() == Qt::Key_R)
        {
            emit sig_reload();
        }
        else if (event->key() == Qt::Key_C)
        {
            emit sig_calcultor();
        }
    }
    else
    {
        QWidget::keyPressEvent(event);
    }
}
