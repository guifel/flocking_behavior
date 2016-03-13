#include "flock.h"
#include "predator.h"
#include "boids.h"
#include "scene.h"
#include "constants.h"
#include "obstacle.h"


Scene::Scene(QWidget *parent) : QWidget(parent)
{

    scene = new QGraphicsScene(0,0,W_S,H_S);


    //Add boids
    for(int i=0;i<INITIAL_NUMBER_OF_FLOCK;i++)
        boidsList.push_back(new Flock);

    for(int i=0;i<INITIAL_NUMBER_OF_PREDATOR;i++)
        boidsList.push_back(new Predator);


    radius = INITIAL_RADIUS;
    globalSpeed = INITIAL_GLOBAL_SPEED;

}
QGraphicsScene* Scene::sceneAddr()
{
    return scene;
}

void Scene::printBoids() const
{
    //Variables for boids propreties
    QVector2D pos(0,0);
    QVector2D speed(0,0);

    //Necessary items to draw a boid
    QGraphicsEllipseItem *printingCircle;
    QGraphicsLineItem *printingLine;

    //Define a pen
    QPen pen;
    pen.setWidth(6);
    pen.setCapStyle(Qt::RoundCap);

    //Erase the previous draw
    scene->clear();

    for(unsigned int i(0);i<boidsList.size();i++) //Go trough the list of boids (flock, predator, obstacle)
    {

        if(!boidsList[i]->isItAnObstacle()) //For flocks and predators
        {


            //Circle print
            pos = boidsList[i]->getPos();
            printingCircle = scene->addEllipse(QRectF(-BOIDS_RAD,-BOIDS_RAD,2*BOIDS_RAD,2*BOIDS_RAD));
            printingCircle->setPos(pos.x(),pos.y());

                //Color
            if(boidsList[i]->isItAPredator()) // Predator
                printingCircle->setBrush(Qt::red);

            else                              // Flock
                printingCircle->setBrush(Qt::blue);

            //Direction indicator
            speed = boidsList[i]->getSpeed();
            speed = speed.normalized()*DIRECTION_ARROW_LENGTH;
            printingLine = scene->addLine(pos.x(),pos.y(),pos.x() + speed.x(),pos.y() + speed.y());
            printingLine->setPen(pen);

        }
        else // For obstacles
        {
            if(boidsList[i]->isItAnObstacle() == SMALL) //Small obstacle
                printingCircle = scene->addEllipse(QRectF(-OBST_SMALL_RAD,-OBST_SMALL_RAD,2*OBST_SMALL_RAD,2*OBST_SMALL_RAD));
            else                                        //Big obstacle
                printingCircle = scene->addEllipse(QRectF(-OBST_BIG_RAD,-OBST_BIG_RAD,2*OBST_BIG_RAD,2*OBST_BIG_RAD));

            pos = boidsList[i]->getPos();
            printingCircle->setPos(pos.x(),pos.y());
            printingCircle->setBrush(Qt::green);
        }

    }
}

void Scene::updateBoids()
{
    QVector2D pos;
    QVector2D speed;
    QVector2D nextPos;
    std::vector<Boids*> neighbours;
    float dist(0);

    for(unsigned int i(0);i<boidsList.size();i++)
    {
        //Check if we have to delet boids since the last iteration
        if(boidsList[i]->getDelete())
        {
            delete boidsList[i];
            boidsList.erase(boidsList.begin()+i);
            if(i == 0) break;
            i--;
        }

        //Skip if it's an obstacle
        if(boidsList[i]->isItAnObstacle()) continue;


        pos = boidsList[i]->getPos();
        speed = boidsList[i]->getSpeed();

        //Clear previous boids neighbours list
        neighbours.clear();

        for(unsigned int k(0);k<boidsList.size();k++)
        {
            //Here we look for neighbours of the boid

            if(k == i) continue; //Skip itself

            //Distance between 2 boids
            dist = (boidsList[k]->getPos() - boidsList[i]->getPos()).length();

            if(dist < radius)
                neighbours.push_back(boidsList[k]); //Add to neighbours list
        }

        //Computing of the new speed by adding the acceleration
        speed = speed + boidsList[i]->acceleration(neighbours)*globalSpeed;

        //Limiting the speed of boids depending on its type (flock/predator)
        if(!boidsList[i]->isItAPredator())
        {
            if(speed.length() > MAX_FLOCK_SPEED) speed = speed.normalized()*MAX_FLOCK_SPEED;
        }
        else
        {
            if(speed.length() > MAX_PREDATOR_SPEED) speed = speed.normalized()*MAX_PREDATOR_SPEED;
        }

        //Set the new speed
        boidsList[i]->setSpeed(speed);

        //Next position
        nextPos = pos + speed*globalSpeed;

        //Boundaries wrapping
        if(nextPos.x() >= W_S)  nextPos.setX(1);
        else if(nextPos.x() <= 0)    nextPos.setX(W_S-1);
        else if(nextPos.y() <= 0)    nextPos.setY(H_S-1);
        else if(nextPos.y() >= H_S)  nextPos.setY(1);

        //Set new position
        boidsList[i]->setPos(nextPos);
    }
}


void Scene::setGlobalSpeed(int coef)
{
    globalSpeed = ((float)coef)/100;
}

void Scene::setRadius(int coef)
{
    radius = coef;
    Flock::setRadius(coef);
}

void Scene::addPredator()
{
    boidsList.push_back(new Predator);
}
void Scene::addSmallObstacle()
{
    boidsList.push_back(new Obstacle(SMALL));
}
void Scene::addBigObstacle()
{
    boidsList.push_back(new Obstacle(BIG));
}
void Scene::delObstacles()
{
    for(unsigned int i(0);i<boidsList.size();i++)
    {
        if(boidsList[i]->isItAnObstacle())
            boidsList[i]->setDelete();
    }
}
void Scene::delPredators()
{
    for(unsigned int i(0);i<boidsList.size();i++)
    {
        if(boidsList[i]->isItAPredator())
            boidsList[i]->setDelete();
    }
}
void Scene::addFLocks()
{
    for(int i=0;i<ADD_FLOCK_BUTTON;i++)
        boidsList.push_back(new Flock);

}
