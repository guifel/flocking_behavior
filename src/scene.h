#ifndef SCENE_H
#define SCENE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
#include <QGraphicsItem>
#include <vector>
#include <QPen>
#include <QVector2D>
#include "boids.h"
#include "flock.h"

class Scene : public QWidget
{
    Q_OBJECT
public:
    Scene(QWidget *parent = 0);    
    QGraphicsScene* sceneAddr(); //Function needed for the display of the scene
    void printBoids() const;     //Graphical function
    void updateBoids();          //Main function for updating boids




private:
    QGraphicsScene *scene;
    std::vector<Boids*> boidsList;   //Main boids list
    float globalSpeed;               //Speed coefficient
    float radius;                    //Neighbour radius



signals:

public slots:
        //Slots link to UI
    void addPredator();
    void addSmallObstacle();
    void addBigObstacle();
    void setGlobalSpeed(int coef);
    void setRadius(int coef);
    void delPredators();
    void delObstacles();
    void addFLocks();
};

#endif // SCENE_H
