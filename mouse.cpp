#include "mouse.h"
#include <QMouseEvent>
#include <QApplication>

void mouse::mousePressEvent_x(QMouseEvent *event){
    global::start_x = event-> x();
}

void mouse::mousePressEvent_y(QMouseEvent *event){
    global::start_y = event->y();
}

void mouse::mouseReleaseEvent_x(QMouseEvent *event){
    global::end_x = event->x();
}

void mouse::mouseReleaseEvent_y(QMouseEvent *event){
    global::end_y = event->y();
}
