#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QMap<QPushButton*,QProcess*> _mapprocess;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
