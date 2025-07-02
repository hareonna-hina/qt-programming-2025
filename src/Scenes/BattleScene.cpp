//
// Created by gerw on 8/20/24.
//

#include <QDebug>
#include "BattleScene.h"
#include "../Items/Characters/Link.h"
#include "../Items/Maps/Battlefield.h"
#include "../Items/Armors/FlamebreakerArmor.h"
#include "../Items/StatusBar.h"

BattleScene::BattleScene(QObject *parent) : Scene(parent) {
    // This is useful if you want the scene to have the exact same dimensions as the view
    setSceneRect(0, 0, 1280, 720);

    map = new Battlefield();
    // 创建两个玩家角色
    character1 = new Link(Character::TYPE_PLAYER1);
    character2 = new Link(Character::TYPE_PLAYER2);

    spareArmor = new FlamebreakerArmor();

    addItem(map);
    addItem(character1);
    addItem(character2);
    addItem(spareArmor);

    map->scaleToFitScene(this);

    // 设置角色起始位置
    // 设置不同位置
    character1->setPos(map->getSpawnPos());   // 玩家1起始位置
    character2->setPos(map->getSpawnPos()+QPointF(100,0));   // 玩家2起始位置

    // 创建玩家1的状态栏
    statusBar_1 = new StatusBar(StatusBar::PLAYER_1, ":/Items/Maps/statusbar1.png", this);
    statusBar_1->setGeometry(10, 10, 200, 100);


    // 创建玩家2的状态栏
    statusBar_2 = new StatusBar(StatusBar::PLAYER_2, ":/path/to/statusbar_background.png", this);
    statusBar_2->setGeometry(1060, 10, 200, 100);


    // spareArmor->unmount();
    // spareArmor->setPos(100, map->getFloorHeight());

}

void BattleScene::processInput() {
    Scene::processInput();
    if (character1 != nullptr) {
        character1->processInput();
    }
    if (character2 != nullptr) {
        character2->processInput();
    }
}

void BattleScene::keyPressEvent(QKeyEvent *event) {
    // 玩家1控制 - WASD
    if (character1 != nullptr) {
        switch (event->key()) {
        case Qt::Key_A:
            character1->setLeftDown(true);
            break;
        case Qt::Key_D:
            character1->setRightDown(true);
            break;
        case Qt::Key_Space:
            character1->setPickDown(true);
            break;
        default:
            Scene::keyPressEvent(event);;
        }
    }

    // 玩家2控制 - 方向键
    if (character2 != nullptr) {
        switch (event->key()) {
        case Qt::Key_Left:
            character2->setLeftDown(true);
            break;
        case Qt::Key_Right:
            character2->setRightDown(true);
            break;
        case Qt::Key_Shift:
            character2->setPickDown(true);
            break;
        default:
            Scene::keyPressEvent(event);;
        }
    }

}

void BattleScene::keyReleaseEvent(QKeyEvent *event) {
    // 玩家1控制 - WASD
    if (character1 != nullptr) {
        switch (event->key()) {
        case Qt::Key_A:
            character1->setLeftDown(false);
            break;
        case Qt::Key_D:
            character1->setRightDown(false);
            break;
        case Qt::Key_Space:
            character1->setPickDown(false);
            break;
        default:
            Scene::keyReleaseEvent(event);
        }
    }

    // 玩家2控制 - 方向键
    if (character2 != nullptr) {
        switch (event->key()) {
        case Qt::Key_Left:
            character2->setLeftDown(false);
            break;
        case Qt::Key_Right:
            character2->setRightDown(false);
            break;
        case Qt::Key_Shift:
            character2->setPickDown(false);
            break;
        default:
            Scene::keyReleaseEvent(event);
        }
    }


}

void BattleScene::update() {
    Scene::update();
}

void BattleScene::processMovement() {
    Scene::processMovement();

    // 更新两个角色的位置
    if (character1 != nullptr) {
        character1->setPos(character1->pos() + character1->getVelocity() * (double) deltaTime);
    }
    if (character2 != nullptr) {
        character2->setPos(character2->pos() + character2->getVelocity() * (double) deltaTime);
    }
}

void BattleScene::processPicking() {
    Scene::processPicking();

    // 处理玩家1的拾取
    if (character1 != nullptr && character1->isPicking()) {

        auto mountable = findNearestUnmountedMountable(character1->pos(), 100.);
        // if (mountable != nullptr) {
        //     spareArmor = dynamic_cast<Armor *>(pickupMountable(character1, mountable));
        // }
    }

    // 处理玩家2的拾取
    if (character2 != nullptr && character2->isPicking()) {

        auto mountable = findNearestUnmountedMountable(character2->pos(), 100.);

        // if (mountable != nullptr) {
        //     spareArmor = dynamic_cast<Armor *>(pickupMountable(character2, mountable));
        // }
    }
}

Mountable *BattleScene::findNearestUnmountedMountable(const QPointF &pos, qreal distance_threshold) {
    Mountable *nearest = nullptr;
    qreal minDistance = distance_threshold;

    for (QGraphicsItem *item: items()) {
        if (auto mountable = dynamic_cast<Mountable *>(item)) {
            if (!mountable->isMounted()) {
                qreal distance = QLineF(pos, item->pos()).length();
                if (distance < minDistance) {
                    minDistance = distance;
                    nearest = mountable;
                }
            }
        }
    }

    return nearest;
}

// Mountable *BattleScene::pickupMountable(Character *character, Mountable *mountable) {
//     // Limitation: currently only supports armor
//     if (auto armor = dynamic_cast<Armor *>(mountable)) {
//         return character->pickupArmor(armor);
//     }
//     return nullptr;
// }

