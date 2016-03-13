#ifndef PREDATOR_H
#define PREDATOR_H

#include "boids.h"
#include <QWidget>

class Predator : public Boids
{

public:
    Predator();

    //Implementation of the acceleration specific to the predator
    virtual QVector2D acceleration(std::vector<Boids*> neighbour);
    //Identifiers
    virtual bool isItAPredator() const;
    virtual int isItAnObstacle() const;



};

#endif // PREDATOR_H
