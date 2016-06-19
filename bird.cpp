#include "bird.h"

Bird::Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(radius*2,radius*2);

    // Create Body
    b2BodyDef bodydef; //bodydef named by me
    bodydef.type = b2_dynamicBody; //00
    bodydef.bullet = true; //00
    bodydef.position.Set(x,y);
    bodydef.userData = this; //00
    g_body = world->CreateBody(&bodydef); //00
    b2CircleShape bodyshape; //00
    bodyshape.m_radius = radius; //00
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = BIRD_DENSITY; //weight
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION; //elastic
    g_body->SetAngularDamping(3); //rotate
    g_body->CreateFixture(&fixturedef); //00

    // Bound timer //combine the pic with the time
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

void Bird::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}
