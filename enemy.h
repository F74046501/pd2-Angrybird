#ifndef ENEMY_H
#define ENEMY_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <global.h>

#define ENEMY_DENSITY 5.0f
#define ENEMY_FRICTION 0.2f
#define ENEMY_RESTITUTION 0.7f

class enemy : public GameItem
{
public:
    enemy(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
};

#endif // ENEMY_H
