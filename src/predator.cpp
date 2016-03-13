#include "predator.h"
#include "constants.h"
#include <qdebug.h>

Predator::Predator()
{

}

QVector2D Predator::acceleration(std::vector<Boids*> neighbour)
{
    float nearest(INITIAL_RADIUS);
    QVector2D nearestPos(0,0);
    Boids* nearestPtr(NULL);
    QVector2D testing;
    QVector2D force;
    float dist(INITIAL_RADIUS);
    bool flockAround(false);

    for(unsigned int i(0);i<neighbour.size();i++)
    {


        //Purchasing the nearest flock
        if(neighbour[i]->isItAPredator() or neighbour[i]->isItAnObstacle())
            continue;

        //Last test passed so there is at leat one flock around
        flockAround = true;


        testing = neighbour[i]->getPos();
        dist =((testing - this->getPos()).length());

        if(dist < nearest)
        {
            nearestPtr = neighbour[i];
            nearestPos = testing;
        }
    }

    if(flockAround) //Flock around !
    {

        if(dist < HIT_DISTANCE) //If the predator hit the flock
        {
            if(nearestPtr)
                nearestPtr->setDelete(); //The predator eat the flock
            //The predator start to go in a random direction
            //return(QVector2D(rand() % INITIAL_SPEED -INITIAL_SPEED/2,rand() % INITIAL_SPEED -INITIAL_SPEED/2));
            return QVector2D(0,0);

        }
        else // Continue to purchase the flock
        {
            //Scaled force toward the nearest flock
            force = (nearestPos - this->getPos()).normalized()*MAX_PREDATOR_SPEED;
            return force;
        }
    }
    else return QVector2D(0,0); //No flock around so continue in the same direction
}

bool Predator::isItAPredator() const
{
    return true;
}

int Predator::isItAnObstacle() const
{
    return false;
}
