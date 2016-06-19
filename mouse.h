#ifndef MOUSE_H
#define MOUSE_H
#include <QMouseEvent>
#include <QApplication>
#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <global.h>

class mouse
{
public:
    void mousePressEvent_x(QMouseEvent *event);
    void mousePressEvent_y(QMouseEvent *event);
    void mouseReleaseEvent_x(QMouseEvent *event);
    void mouseReleaseEvent_y(QMouseEvent *event);
};

#endif // MOUSE_H
