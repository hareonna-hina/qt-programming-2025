//
// Created by gerw on 8/20/24.
//
#include "MyGame.h"
#include "Scenes/BattleScene.h"

MyGame::MyGame(QWidget *parent) : QMainWindow(parent) {

    battleScene = new BattleScene(this);

    view = new QGraphicsView(this);
    view->setScene(battleScene);

    // Set the view's window size to 1280x720
    view->setFixedSize(1280, 720);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    setCentralWidget(view);

    // Adjust the QMainWindow size to tightly wrap the QGraphicsView
    setFixedSize(1280,720);
    battleScene->startLoop();

}
