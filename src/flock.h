#ifndef FLOCK_H
#define FLOCK_H

#include "boids.h"
#include <QWidget>


class Flock : public Boids
{

public:
    Flock();

    //Implementation of the acceleration for flocks
    virtual QVector2D acceleration(std::vector<Boids*> neighbour);

    //Identifications fuctions
    virtual bool isItAPredator() const;
    virtual int isItAnObstacle() const;

    //Static functions to set global flocks parameters
    static void setWeight(int coh, int ali, int sep);
    static void setRadius(int rad);


signals:

public slots:

private:

    //Intermediate computation for acceleration
    QVector2D separation(std::vector<Boids*> neighbour) const;
    QVector2D cohesion(std::vector<Boids*> neighbour) const;
    QVector2D alignment(std::vector<Boids*> neighbour) const;
    QVector2D escape(Boids* predator) const;


    //Static variables commons for every flocks
    static float  separationWeight;
    static float alignmentWeight;
    static float cohesionWeight;
    static int radius;


};

#endif // FLOCK_H
