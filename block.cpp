#include "block.h"

block::block(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(w,h);

    // Create Body
    b2BodyDef bodydef; //bodydef named by me
    bodydef.type = b2_dynamicBody; //00
    bodydef.bullet = true; //00
    bodydef.position.Set(x,y);
    bodydef.userData = this; //00
    g_body = world->CreateBody(&bodydef); //00
    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w,h);
    b2FixtureDef fixturedef;
    fixturedef.density = BLOCK_DENSITY; //weight
    fixturedef.friction = BLOCK_FRICTION;
    fixturedef.restitution = BLOCK_RESTITUTION; //elastic
    g_body->SetAngularDamping(3); //rotate
    g_body->CreateFixture(&bodyBox,9.0f); //00

    // Bound timer //combine the pic with the time
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

void block::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}


