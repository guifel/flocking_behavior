#include "boids.h"
#include "flock.h"
#include "constants.h"


float Flock::cohesionWeight = 0.5;
float Flock::alignmentWeight = 0.5;
float Flock::separationWeight = 0.5;
int Flock::radius = 100;


Flock::Flock()
{

}

QVector2D Flock::acceleration(std::vector<Boids*> neighbour)
{    
    QVector2D acceleration;
    Boids* predator(NULL);
    std::vector<Boids*> obstacles;

     //Looking for predator nearby and obstacle
     for(unsigned int i(0);i<neighbour.size();i++)
     {
         if(neighbour[i]->isItAPredator())
             // Predator nearby !
             predator = neighbour[i];
         else if(neighbour[i]->isItAnObstacle())
         {
            //Obstacle nearby, move object to obstacle list
            obstacles.push_back(neighbour[i]);
            neighbour.erase(neighbour.begin()+i);
            if(i == 0) break;
            i--;

         }
     }

    if(predator == NULL)
    {
    //Applying flocking rules
    QVector2D sep = separation(neighbour);
    QVector2D coh = cohesion(neighbour)*cohesionWeight;
    QVector2D ali = alignment(neighbour)*alignmentWeight;

    QVector2D obst = obstacleForce(obstacles);

    //Sum component of the acceleration
    acceleration =  sep + coh + ali + obst;

    //Final normalization of the resulting acceleration
    acceleration.normalize();
    }
    else //There is a predator flocks have to run away flocking rules doesn't matter
    {
       QVector2D obst = obstacleForce(obstacles);
        acceleration = escape(predator) + obst;
        acceleration.normalize();
    }
    return acceleration;
}

QVector2D Flock::separation(std::vector<Boids*> neighbour) const
{

    QVector2D dist;
    QVector2D meanPos;


    if(neighbour.size() == 0) return QVector2D(0,0);

    for(unsigned int i(0);i<neighbour.size();i++)
    {
        dist = this->getPos() - neighbour[i]->getPos();

        // Force resulting only if a flock is in the neighbour radius reduce by de separation coefficient
        if(dist.length() < ((float)radius)*separationWeight)
            meanPos += dist;

    }

    //Scaling the separation force
    meanPos = meanPos*SEPARATION_FORCE;


    return meanPos;
}

QVector2D Flock::cohesion(std::vector<Boids*> neighbour) const
{
    QVector2D meanPos;
    QVector2D force;

    if(neighbour.size() == 0) return QVector2D(0,0);

    //Average postion among neighbours
    for(unsigned int i(0);i<neighbour.size();i++)
    {
        meanPos += neighbour[i]->getPos();
    }

    meanPos /= neighbour.size();

    //Force directed to the average position
    force = meanPos - this->getPos();

    return force*COHESION_FORCE;
}

QVector2D Flock::alignment(std::vector<Boids*> neighbour) const
{
    QVector2D meanSpeed;


    if(neighbour.size() == 0) return QVector2D(0,0);

    //Average speed among neighbours
    for(unsigned int i(0);i<neighbour.size();i++)
    {
        meanSpeed += neighbour[i]->getSpeed();
    }

    meanSpeed /= neighbour.size();

    return meanSpeed*ALIGNMENT_FORCE;
}

QVector2D Flock::escape(Boids* predator) const
{

    QVector2D force;
    //Escape force away from the predator set at the maximum speed
    force = (this->getPos() - predator->getPos()).normalized()*MAX_FLOCK_SPEED;
    return force*ESCAPE_FORCE;
}

void Flock::setWeight(int coh, int ali, int sep)
{
    cohesionWeight = ((float)coh)/100;
    alignmentWeight = ((float)ali)/100;
    separationWeight = ((float)sep)/100;
}

void Flock::setRadius(int rad)
{
    radius = rad;
}

bool Flock::isItAPredator() const
{
    return false;
}

int Flock::isItAnObstacle() const
{
    return false;
}


