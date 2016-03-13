#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QTimer>

class Scene;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void updateScene();     // Call every 15ms
    void updateWeight();    //Weight sliders slot

private:
    Ui::MainWindow *ui;
    Scene *myScene;
    QTimer *timer;

};

#endif // MAINWINDOW_H
