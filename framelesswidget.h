#ifndef FRAMELESSWIDGET_H
#define FRAMELESSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QMenu>
#include <QProcess>
#include <QCoreApplication>
#include <QFileDialog>
#include <QKeySequence>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMenuBar>
#include "jsonioctrl.hpp"

#include <iostream>
#include <string>
#include <cstdlib>

class FramelessWidget : public QLabel
{
    Q_OBJECT

//    enum ResizeDir{
//        Nodir,
//        Top = 0x01,
//        Bottom = 0x02,
//        Left = 0x04,
//        Right = 0x08,
//        TopLeft = Top | Left,
//        TopRight = Top | Right,
//        BottomLeft = Bottom | Left,
//        BottomRight = Bottom | Right
//    };

public:
    explicit FramelessWidget(QWidget *parent = 0);
    ~FramelessWidget();

signals:
    void sig_calcultor();
    void sig_reload();
    void sig_config();
    void sig_doubleclicked(QPoint pos);
    void sig_exit();

private:
//    ResizeDir _resizeDir;
    QPoint _dragPosition;
//    int _edgeMargin;
//    bool _dragtonormal;
    QMenu* _contextmenu;

private:
//    void testEdge();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    // QWidget interface
protected:
    void mouseDoubleClickEvent(QMouseEvent *event);

    // QWidget interface
protected:
    void contextMenuEvent(QContextMenuEvent *event);

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // FRAMELESSWIDGET_H
