#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <ctime>
#include <stdlib.h>
#include <QPushButton>
#include <QWidget>
#include <QPoint>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{

    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);

    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));

    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());

    // Create ground (You can edit here)
    itemList.push_back(new Land(16,1.5,32,3,QPixmap(":/image/background.png").scaled(width(),height()/6.0),world,scene));

    // Create object (You can edit here)
    //Bird *birdie = new Bird(2.0f,5.0f,0.27f,&timer,QPixmap(":/bird.png").scaled(height()/9.0,height()/9.0),world,scene);
    pig = new enemy(20.0f,5.0f,0.27f,&timer,QPixmap(":/image/pig.png").scaled(height()/9.0,height()/9.0),world,scene);
    joey1 = new enemy(15.0f,3.0f,0.35f,&timer,QPixmap(":/image/head.png").scaled(height()/9.0,height()/9.0),world,scene);
    joey2 = new enemy(16.0f,5.0f,0.35f,&timer,QPixmap(":/image/head.png").scaled(height()/9.0,height()/9.0),world,scene);
    joey3 = new enemy(16.0f,7.0f,0.35f,&timer,QPixmap(":/image/head.png").scaled(height()/9.0,height()/9.0),world,scene);
    joey4 = new enemy(17.0f,7.0f,0.35f,&timer,QPixmap(":/image/head.png").scaled(height()/9.0,height()/9.0),world,scene);
    joey5 = new enemy(17.0f,9.0f,0.35f,&timer,QPixmap(":/image/head.png").scaled(height()/9.0,height()/9.0),world,scene);
    joey6 = new enemy(17.0f,11.0f,0.35f,&timer,QPixmap(":/image/head.png").scaled(height()/9.0,height()/9.0),world,scene);
    wood = new block(30.0f,20.0f,0.5f,5.0f,&timer,QPixmap(":/image/thinwood1.png").scaled(height()/9.0,height()/2.0),world,scene);

    //music
    music->setMedia(QUrl("qrc:/image/kokokoko.mp3"));
    music->play();

    // Setting the Velocity
    //birdie->setLinearVelocity(b2Vec2(0,0));
    //itemList.push_back(birdie);???????????????????????//

    // button re
    QIcon *btn = new QIcon(QPixmap(":/image/nii.png"));
    QPushButton *restart = new QPushButton(*btn,"re");
    restart->setIconSize(QSize(75,75));
    restart->setFixedSize(110,75);
    restart->setGeometry(830,30,200,100);
    scene->addWidget(restart);
    connect(restart,SIGNAL(clicked()),this,SLOT(restart()));

    // button start
    QIcon *bn = new QIcon(QPixmap(":/image/nii.png"));
    QPushButton *start = new QPushButton(*bn,"start");
    start->setIconSize(QSize(75,75));
    start->setFixedSize(110,75);
    start->setGeometry(830,110,200,100);
    scene->addWidget(start);
    connect(start,SIGNAL(clicked()),this,SLOT(start()));

    // button end
    QIcon *bt = new QIcon(QPixmap(":/image/end.png"));
    QPushButton *end = new QPushButton(*bt,"");
    end->setIconSize(QSize(75,75));
    end->setFixedSize(75,75);
    end->setGeometry(700,30,200,100);
    scene->addWidget(end);
    connect(end,SIGNAL(clicked()),this,SLOT(close()));

    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);

}

//flag = 0->original ; flag = 1->could kill ; flag = 2->pig died
int flag= 0;

//global::start_x is crucial means a step

//record the birdie2 fly or not
int bird2 = 0;

//record the egg released or not ; 1 has flyed ; 0 not flyed
int egg_count=0;

//record the bird4 fly or not
int bird4 = 0;

//have accerleated
int yellow_a=0;

//record the bird5 fly or not
int bird5 = 0;

//have dropped
int black_a=0;

//record the bird6 fly or not
int bird6 = 0;

//have dropped
int green_a=0;

//run back
int green_back=0;

//for itemList
int standard=0;
bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(global::start_x==0) global::start_x = 100;
        if(global::start_x==200) global::start_x=300;
        if(global::start_x==400) global::start_x=500;
        if(global::start_x==600) global::start_x=700;
        if(global::start_x==800) global::start_x=900;
    }

    if(event->type() == QEvent::MouseMove)
    {
        //dissappear
        if(flag==1)
            if(pig->g_body->GetPosition().x>20){
                delete pig;
                flag=2;
            }

        //egg
        if(bird2==1 && egg_count==0)
            if(birdie2->g_body->GetPosition().x > 5){
                birdie3 = new Bird(4.0f,8.0f,0.2f,&timer,QPixmap(":/image/egg.png").scaled(height()/9.0,height()/9.0),world,scene);

                birdie3->setLinearVelocity(b2Vec2(7+(rand()%1000)/100,0));

                egg_count = 1;
            }

        //accerelate
        if(bird4==1 && yellow_a==0)
            if(birdie4->g_body->GetPosition().x>15){
                birdie4->setLinearVelocity(b2Vec2(30,-3));
                yellow_a=1;
        }

        //drop
        if(bird5==1 && black_a==0)
            if(birdie5->g_body->GetPosition().x>18){
                birdie5->setLinearVelocity(b2Vec2(0,-13));
                black_a=1;
        }

        //accerelate -
        if(bird6==1 & green_a==0)
            if(birdie6->g_body->GetPosition().x>14){
                birdie6->setLinearVelocity(b2Vec2(-30,-3));
                green_a=1;
        }
    }

    if(event->type() == QEvent::MouseButtonRelease)
    {
        if(global::start_x == 100 ){
            birdie1 = new Bird(2.0f,3.0f,0.27f,&timer,QPixmap(":/bird.png").scaled(height()/9.0,height()/9.0),world,scene);

            unsigned seed = (unsigned)time(NULL);
            birdie1->setLinearVelocity(b2Vec2(7+(rand()%1000)/80,8+(rand()%1000)/80));

            flag = 1; //have flyed
            global::start_x =200;
        }

        if(global::start_x == 300 ){
            birdie2 = new Bird(2.0f,3.0f,0.27f,&timer,QPixmap(":/image/white.png").scaled(height()/9.0,height()/9.0),world,scene);

            unsigned seed = (unsigned)time(NULL);
            birdie2->setLinearVelocity(b2Vec2(5+(rand()%1000)/80,7+(rand()%1000)/80));

            bird2 = 1; //have flyed for special function
            global::start_x =400;
        }

        if(global::start_x == 500 ){
            birdie4 = new Bird(2.0f,3.0f,0.27f,&timer,QPixmap(":/image/yellow.png").scaled(height()/9.0,height()/9.0),world,scene);

            unsigned seed = (unsigned)time(NULL);
            birdie4->setLinearVelocity(b2Vec2(7+(rand()%1000)/80,7+(rand()%1000)/80));

            bird4 = 1; //have flyed for special function
            global::start_x =600;
        }

        if(global::start_x == 700 ){
            birdie5 = new Bird(2.0f,3.0f,0.27f,&timer,QPixmap(":/image/black.png").scaled(height()/9.0,height()/9.0),world,scene);

            unsigned seed = (unsigned)time(NULL);
            birdie5->setLinearVelocity(b2Vec2(9+(rand()%1000)/80,9+(rand()%1000)/80));

            bird5 = 1; //have flyed for special function
            global::start_x =800;
        }

        if(global::start_x == 900 ){
            birdie6 = new Bird(2.0f,3.0f,0.27f,&timer,QPixmap(":/image/green.png").scaled(height()/9.0,height()/9.0),world,scene);

            unsigned seed = (unsigned)time(NULL);
            birdie6->setLinearVelocity(b2Vec2(9+(rand()%1000)/100,12+(rand()%1000)/100));

            bird6 = 1; //have flyed for special function
            global::start_x =1000;
        }

    }
    return false;
}

void MainWindow::restart(){
    delete wood;    
    delete joey1;
    delete joey2;
    delete joey3;
    delete joey4;
    delete joey5;
    delete joey6;
    delete birdie1;
    delete birdie2;
    delete birdie3;
    delete birdie4;
    delete birdie5;
    delete birdie6;
}

void MainWindow::start(){
    itemList.push_back(new Land(16,1.5,32,3,QPixmap(":/image/background.png").scaled(width(),height()/6.0),world,scene));

    pig = new enemy(20.0f,5.0f,0.27f,&timer,QPixmap(":/image/pig.png").scaled(height()/9.0,height()/9.0),world,scene);
    joey1 = new enemy(15.0f,3.0f,0.35f,&timer,QPixmap(":/image/head.png").scaled(height()/9.0,height()/9.0),world,scene);
    joey2 = new enemy(16.0f,5.0f,0.35f,&timer,QPixmap(":/image/head.png").scaled(height()/9.0,height()/9.0),world,scene);
    joey3 = new enemy(16.0f,7.0f,0.35f,&timer,QPixmap(":/image/head.png").scaled(height()/9.0,height()/9.0),world,scene);
    joey4 = new enemy(17.0f,7.0f,0.35f,&timer,QPixmap(":/image/head.png").scaled(height()/9.0,height()/9.0),world,scene);
    joey5 = new enemy(17.0f,9.0f,0.35f,&timer,QPixmap(":/image/head.png").scaled(height()/9.0,height()/9.0),world,scene);
    joey6 = new enemy(17.0f,11.0f,0.35f,&timer,QPixmap(":/image/head.png").scaled(height()/9.0,height()/9.0),world,scene);
    wood = new block(30.0f,20.0f,0.5f,5.0f,&timer,QPixmap(":/image/thinwood1.png").scaled(height()/9.0,height()/2.0),world,scene);

    global::start_x = 0;//restart for the bird to fly
    bird2=0;
    egg_count=0;//let the white bird to use special
    bird4=0;
    yellow_a=0;//let the yellow bird to fly again
    bird5=0;
    black_a=0;//let the black bird to fly again
    bird6=0;
    green_a=0;//let the black bird to fly again
    green_back=0;//let the green fly back again

}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

