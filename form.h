#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "advancedtoolbox.h"
#include <QFrame>
#include <QPushButton>
#include <QDebug>
#include <QToolBar>
#include <QObject>
#include <QVBoxLayout>
#include <QProcess>
#include "jsonioctrl.hpp"

namespace Ui {
class Form;
}

class Form : public AdvancedToolBox
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    QMap<QPushButton*,QProcess*> _mapprocess;

private:
    Ui::Form *ui;
    bool _show;
    bool _first;
    bool _adjustsize;
    QPoint _lastshown;

    void load();

public slots:
    void slot_doubleclick_show(QPoint pos);
    void slot_reload();

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // FORM_H
