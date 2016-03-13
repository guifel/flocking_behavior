#ifndef BOIDS_H
#define BOIDS_H

#include <QWidget>
#include <QVector2D>
#include <stdlib.h>
#include <time.h>

//Abstract base class for predator, flocks and obstacles

class Boids
{

public:
    Boids();
    ~Boids();
    //accessors
    QVector2D getPos() const;
    QVector2D getSpeed() const;
    bool getDelete() const;
    void setDelete();

    //set parameters
    void setPos(QVector2D p);
    void setSpeed(QVector2D p);

    //Calculate the force when a boids is next to an obstacle
    //taking the list of obstacles nearby
    QVector2D obstacleForce(std::vector<Boids*> obstacles) const;

    //Pure virtuals
    virtual QVector2D acceleration(std::vector<Boids*> neighbour) =0;
    virtual bool isItAPredator() const =0;
    virtual int isItAnObstacle() const =0; //return 1 for a small obstacle 2 for a big 0 for somthing else

private:

    //Boids propreties
    QVector2D pos;
    QVector2D speed;
protected:

    bool toDelet;

};

#endif // BOIDS_H
