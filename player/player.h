#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QIcon>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QMouseEvent>
#include <QKeyEvent>

namespace Ui {
class Player;
}

class Player : public QWidget
{
    Q_OBJECT

    enum ResizeDir{
        Nodir,
        Top = 0x01,
        Bottom = 0x02,
        Left = 0x04,
        Right = 0x08,
        TopLeft = Top | Left,
        TopRight = Top | Right,
        BottomLeft = Bottom | Left,
        BottomRight = Bottom | Right
    };

public:
    explicit Player(QWidget *parent = nullptr);
    ~Player();

private:
    Ui::Player *ui;

private:
    ResizeDir _resizeDir;
    QPoint _dragPosition;
    int _edgeMargin;
    bool _dragtonormal;

    QSystemTrayIcon *_tray_icon;
    QMenu* _tray_menu;

private:
    void testEdge();
    void systemtraymenu();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_toolButton_clicked();
};

#endif // PLAYER_H
