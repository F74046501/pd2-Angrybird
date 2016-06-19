#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <enemy.h>
#include <block.h>
#include <global.h>
#include <QMediaPlayer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    enemy *pig;
    enemy *joey1;
    enemy *joey2;
    enemy *joey3;
    enemy *joey4 ;
    enemy *joey5;
    enemy *joey6;
    block *wood;
    Bird *birdie1;
    Bird *birdie2;
    Bird *birdie3;
    Bird *birdie4;
    Bird *birdie5;
    Bird *birdie6;

signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void restart();
    void start();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    QMediaPlayer *music = new QMediaPlayer();

};

#endif // MAINWINDOW_H
