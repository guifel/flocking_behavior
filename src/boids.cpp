#include "boids.h"
#include "constants.h"
Boids::Boids()
{
    // Set a random postion and speed
    pos.setX(rand() % W_S);
    pos.setY(rand() % H_S);
    speed.setX(rand() % INITIAL_SPEED -INITIAL_SPEED/2);
    speed.setY(rand() % INITIAL_SPEED -INITIAL_SPEED/2);

    toDelet = false;

}

QVector2D Boids::getPos() const
{
    return pos;
}

QVector2D Boids::getSpeed() const
{
    return speed;
}
void Boids::setPos(QVector2D p)
{
    pos = p;
}
void Boids::setSpeed(QVector2D p)
{
    speed = p;
}

QVector2D Boids::obstacleForce(std::vector<Boids*> obstacles) const
{
    QVector2D dist;
    QVector2D meanPos;
    QVector2D force;


    if(obstacles.size() == 0) return QVector2D(0,0);

    for(unsigned int i(0);i<obstacles.size();i++)
    {
        dist = this->getPos() - obstacles[i]->getPos();

       //differentiating big or small obstacle
       if(obstacles[i]->isItAnObstacle() == SMALL)
       {

            if(dist.length() < OBST_SMALL_RAD + OBST_DIST)
                meanPos += dist;
       }
       else
       {
            if(dist.length() < OBST_BIG_RAD + OBST_DIST)
                meanPos += dist;
       }
    }

    //multiplying by obstacle force coeffcient
    meanPos = meanPos*OBSTACLE_FORCE;

    //Make the force tengent to the obstacle
    force = QVector2D(meanPos.y(),-meanPos.x());

    return force;

}

bool Boids::getDelete() const
{
    return toDelet;
}

void Boids::setDelete()
{
    toDelet = true;
}

Boids::~Boids()
{

}

