//
// Created by gerw on 8/20/24.
//

#ifndef QT_PROGRAMMING_2024_BATTLESCENE_H
#define QT_PROGRAMMING_2024_BATTLESCENE_H

#include <QKeyEvent>
#include "Scene.h"
#include "../Items/Maps/Map.h"
#include "../Items/Characters/Character.h"
#include "../Items/StatusBar.h"
#include "../Items/Weapon.h"
#include <QList>

class BattleScene : public Scene {
Q_OBJECT

public:
    explicit BattleScene(QObject *parent);

    void processInput() override;

    void processMovement() override;

    void processPicking() override;

    void showVictory(Character::CharacterType type);

    void createWeapons();

    QList <Weapon*> weapons;

protected slots:

    void update() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

private:

    Mountable *findNearestUnmountedMountable(const QPointF &pos, qreal distance_threshold = std::numeric_limits<qreal>::max());

    static Mountable * pickupMountable(Character *character, Mountable *mountable);

    Map *map;
    Character *character1;
    Character *character2;
    Armor *spareArmor;
    StatusBar* statusBar_1;
    StatusBar* statusBar_2;
    QGraphicsPixmapItem* victoryImage = nullptr;
    void checkGameOver();
};


#endif //QT_PROGRAMMING_2024_BATTLESCENE_H
