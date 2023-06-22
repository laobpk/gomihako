#ifndef TESTICON_H
#define TESTICON_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class testicon;
}

class testicon : public QWidget
{
    Q_OBJECT

public:
    explicit testicon(QWidget *parent = 0);
    ~testicon();

    void add_mainwindow(QWidget* w);

private slots:
    void on_pushButton_clicked();

private:
    Ui::testicon *ui;
    bool _hidden;
    QWidget* _ptr;

};

#endif // TESTICON_H
