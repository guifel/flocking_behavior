#include "obstacle.h"
#include "boids.h"
#include "constants.h"

Obstacle::Obstacle(int size)
{
    // Set the size

    if(size == BIG) big = true;
    else big = false;

    //An obstacle has no speed
    this->setSpeed(QVector2D(0,0));

}

QVector2D Obstacle::acceleration(std::vector<Boids*> neighbour)
{
    //Null acceleration
    return QVector2D(0,0);
}

bool Obstacle::isItAPredator() const
{
    return false;
}

int Obstacle::isItAnObstacle() const
{
    if(big)
        return BIG;
    else
        return SMALL;
}

