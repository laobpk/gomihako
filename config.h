#ifndef CONFIG_H
#define CONFIG_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QDateTime>
#include <QFileDialog>
#include "jsonioctrl.hpp"

namespace Ui {
class config;
}

class config : public QMainWindow
{
    Q_OBJECT

public:
    explicit config(QWidget *parent = 0);
    ~config();

    void readconfig();

public slots:
    void reload();

private slots:
    void on_btn_saveone_clicked();

    void on_btn_saveall_clicked();

    void on_btn_page_clicked();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_actionadd_program_triggered();

    void on_actionadd_page_triggered();

private:
    Ui::config *ui;
};

#endif // CONFIG_H
