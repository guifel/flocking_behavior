#include "scene.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QDebug>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Display UI
    ui->setupUi(this);

    //Set time for random numbers
    srand (time(NULL));

    //Creat the scene
    myScene = new Scene;

    //Link the scene to the view and display
    ui->view->setScene(myScene->sceneAddr());
    ui->view->show();

    // connect UI
    connect(ui->radiusSlider, SIGNAL(valueChanged(int)),myScene,SLOT(setRadius(int)));
    connect(ui->speedSlider, SIGNAL(valueChanged(int)),myScene,SLOT(setGlobalSpeed(int)));
    connect(ui->separationSlider, SIGNAL(valueChanged(int)),this,SLOT(updateWeight()));
    connect(ui->cohesionSlider, SIGNAL(valueChanged(int)),this,SLOT(updateWeight()));
    connect(ui->alignmentSlider, SIGNAL(valueChanged(int)),this,SLOT(updateWeight()));
    connect(ui->addPredator,SIGNAL(clicked(bool)),myScene,SLOT(addPredator()));
    connect(ui->addSmallObstacle,SIGNAL(clicked(bool)),myScene,SLOT(addSmallObstacle()));
    connect(ui->AddBigObstacle,SIGNAL(clicked(bool)),myScene,SLOT(addBigObstacle()));
    connect(ui->delObstacles,SIGNAL(clicked(bool)),myScene,SLOT(delObstacles()));
    connect(ui->delPredators,SIGNAL(clicked(bool)),myScene,SLOT(delPredators()));
    connect(ui->addFlock,SIGNAL(clicked(bool)),myScene,SLOT(addFLocks()));

    //main timer for animation call every 15ms
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateScene()));
    timer->start(15);
}

void MainWindow::updateScene()
{
      myScene->printBoids();
      myScene->updateBoids();
}



void MainWindow::updateWeight()
{
    Flock::setWeight(ui->cohesionSlider->value(),
                     ui->alignmentSlider->value(),
                     ui->separationSlider->value());

}

MainWindow::~MainWindow()
{
    delete ui;
}

