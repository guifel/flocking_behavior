#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "boids.h"

class Obstacle : public Boids
{
public:
    Obstacle(int size); //Set the size of the obstacle in parameter

    virtual QVector2D acceleration(std::vector<Boids*> neighbour);
    virtual bool isItAPredator() const;
    virtual int isItAnObstacle() const;

private:
    bool big; //Is it a big obstacle ?
};

#endif // OBSTACLE_H
