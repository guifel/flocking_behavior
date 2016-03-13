#-------------------------------------------------
#
# Project created by QtCreator 2016-01-16T18:32:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project1
TEMPLATE = app


SOURCES = main.cpp\
        mainwindow.cpp \
        scene.cpp \
    boids.cpp \
    flock.cpp \
    predator.cpp \
    obstacle.cpp

HEADERS  = mainwindow.h \
            scene.h \
            boids.h \
            flock.h \
            predator.h \
            constants.h \
    obstacle.h

FORMS    = mainwindow.ui
