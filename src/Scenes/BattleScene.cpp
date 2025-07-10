//
// Created by gerw on 8/20/24.
//

#include <QDebug>
#include "BattleScene.h"
#include "../Items/Characters/Link.h"
#include "../Items/Maps/Battlefield.h"
#include "../Items/Armors/FlamebreakerArmor.h"
#include "../Items/StatusBar.h"
#include <QDateTime>
#include "../Items/Fist.h"
#include "../Items/Knife.h"
#include "../Items/Bullet.h"
#include "../Items/Rifle.h"
#include "../Items/Sniper.h"
#include "../Items/SolidBall.h"
#include "../Items/Projectile.h"

BattleScene::BattleScene(QObject *parent) : Scene(parent) {
    // This is useful if you want the scene to have the exact same dimensions as the view
    setSceneRect(0, 0, 1280, 720);

    map = new Battlefield();
    // 创建两个玩家角色
    character1 = new Link(Character::TYPE_PLAYER1);
    character2 = new Link(Character::TYPE_PLAYER2);

    //spareArmor = new FlamebreakerArmor();

    addItem(map);
    addItem(character1);
    addItem(character2);
    //addItem(spareArmor);

    map->scaleToFitScene(this);

    // 设置角色起始位置
    // 设置不同位置
    character1->setPos(110,440);   // 玩家1起始位置
    character2->setPos(1180,440);   // 玩家2起始位置

    // 创建玩家1的状态栏
    statusBar_1 = new StatusBar(StatusBar::PLAYER_1, ":/Items/Maps/Battlefield/statusbar1.png", this);
    statusBar_1->setGeometry(10, 10, 200, 100);


    // 创建玩家2的状态栏
    statusBar_2 = new StatusBar(StatusBar::PLAYER_2, ":/Items/Maps/Battlefield/statusbar2.png", this);
    statusBar_2->setGeometry(1060, 10, 200, 100);

    // 初始生命值显示
    statusBar_1->updateHearts(character1->getHealth());
    statusBar_2->updateHearts(character2->getHealth());

    createWeapons();


}

void BattleScene::createWeapons()
{
    // 小刀
    Knife* knife = new Knife(nullptr);
    knife->setPos(200, 300);
    addItem(knife);
    weapons.append(knife);

    // 实心球
    SolidBall* solidBall = new SolidBall(nullptr);
    solidBall->setPos(400, 300);
    addItem(solidBall);
    weapons.append(solidBall);

    // 步枪
    Rifle* rifle = new Rifle(nullptr);
    rifle->setPos(600, 300);
    addItem(rifle);
    weapons.append(rifle);

    // 狙击枪
    Sniper* sniper = new Sniper(nullptr);
    sniper->setPos(600, 400);
    addItem(sniper);
    weapons.append(sniper);
    // 拳头不需要创建，因为人物自带
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
    // 如果有胜利图片，禁用所有输入
    if (victoryImage)
    {
        return;
    }
    // 玩家1控制 - WASD
    if (character1 != nullptr) {
        switch (event->key()) {
        case Qt::Key_A:
            if(!character1->is_squating)
            {
                character1->setLeftDown(true);
            }
            break;
        case Qt::Key_D:
            if(!character1->is_squating)
            {
                character1->setRightDown(true);
            }
            break;
        case Qt::Key_S:
            character1->setPickDown(true);
            if(event->isAutoRepeat())
            {
                return;
            }
            if(!character1->is_squating && character1->m_squatStartTime == 0)
            {
                character1->m_squatStartTime=QDateTime::currentMSecsSinceEpoch();
            }
            break;
        case Qt::Key_W:
            if(event->isAutoRepeat()) return;
            if(!character1->is_squating&&!character1->is_jumping&&character1->getOnGround())
            {
                character1->setJumpDown(true);
                character1->is_jumping=true;
            }
            break;
        default:
            Scene::keyPressEvent(event);;
        }
    }

    // 玩家2控制 - 方向键
    if (character2 != nullptr) {
        switch (event->key()) {
        case Qt::Key_Left:
            if(!character2->is_squating)
            {
                character2->setLeftDown(true);
            }
            break;
        case Qt::Key_Right:
            if(!character2->is_squating)
            {
                character2->setRightDown(true);
            }
            break;
        case Qt::Key_Down:
            if(event->isAutoRepeat())
            {
                return;
            }
            character2->setPickDown(true);
            if(!character2->is_squating&& character2->m_squatStartTime == 0)
            {
                character2->m_squatStartTime=QDateTime::currentMSecsSinceEpoch();
            }
            break;
        case Qt::Key_Up:
            if(event->isAutoRepeat()) return;
            if(!character2->is_squating&&!character2->is_jumping&&character2->getOnGround())
            {
                character2->setJumpDown(true);
            }
            break;
        default:
            Scene::keyPressEvent(event);;
        }
    }

}

void BattleScene::keyReleaseEvent(QKeyEvent *event) {
    // 如果有胜利图片，禁用所有输入
    if (victoryImage)
    {
        return;
    }
    // 玩家1控制 - WASD
    if (character1 != nullptr) {
        switch (event->key()) {
        case Qt::Key_A:
            character1->setLeftDown(false);
            break;
        case Qt::Key_D:
            character1->setRightDown(false);
            break;
        case Qt::Key_S:
            if(event->isAutoRepeat())
            {
                return;
            }
            character1->setPickDown(false);
            character1->setSquatDown(false);
            character1->is_squating=false;
            if (QDateTime::currentMSecsSinceEpoch() - character1->m_squatStartTime > character1->JITTER_THRESHOLD)
            {
                character1->m_squatStartTime = 0;
            }
            break;
        case Qt::Key_W:
            if(event->isAutoRepeat()) return;
            character1->setJumpDown(false);
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
        case Qt::Key_Down:
            if(event->isAutoRepeat())
            {
                return;
            }
            character2->setPickDown(false);
            character2->setSquatDown(false);
            character2->is_squating=false;
            if (QDateTime::currentMSecsSinceEpoch() - character2->m_squatStartTime > character2->JITTER_THRESHOLD)
            {
                character2->m_squatStartTime = 0;
            }
            break;
        case Qt::Key_Up:
            if(event->isAutoRepeat()) return;
            character2->setJumpDown(false);
            break;
        default:
            Scene::keyReleaseEvent(event);
        }
    }


}

void BattleScene::update() {
    if (character1 != nullptr) {
        if (character1->isPickDown() && !character1->is_squating) {
            qint64 diff = QDateTime::currentMSecsSinceEpoch() - character1->m_squatStartTime;
            if (diff >= 500) {
                character1->is_squating = true;
                character1->setSquatDown(true);
            }
        }
        character1->applyGravity(deltaTime);
        character1->checkCollisions(map);
        character1->differentTerrain(map);
    }
    if (character2 != nullptr) {
        if (character2->isPickDown() ) {
            qint64 diff = QDateTime::currentMSecsSinceEpoch() - character2->m_squatStartTime;
            if (diff >= 500) {
                character2->is_squating = true;
                character2->setSquatDown(true);
            }
        }
        character2->applyGravity(deltaTime);
        character2->checkCollisions(map);
        character2->differentTerrain(map);
    }
    // 检查碰撞和游戏结束
    if (character1 != nullptr && character1->isAlive())
    {
        character1->checkProjectileCollisions();
    }
    if (character2 != nullptr && character2->isAlive())
    {
        character2->checkProjectileCollisions();
    }

    checkGameOver();
    Scene::update();
}

void BattleScene::checkGameOver()
{
    if (victoryImage) return;

    // 检查玩家死亡
    if (character1 && !character1->isAlive()) {
        showVictory(character2->characterType());
    } else if (character2 && !character2->isAlive()) {
        showVictory(character1->characterType());
    }
}

void BattleScene::showVictory(Character::CharacterType winner)
{
    // 加载胜利图片
    QString imagePath;
    if (winner == Character::TYPE_PLAYER1)
    {
        imagePath = ":/Items/Victory/player1_victory.png";
    }
    else
    {
        imagePath = ":/Items/Victory/player2_victory.png";
    }

    QPixmap victoryPixmap(imagePath);
    if (!victoryPixmap.isNull())
    {
        victoryImage = new QGraphicsPixmapItem(victoryPixmap);
        // 居中显示
        victoryImage->setPos((width() - victoryPixmap.width()) / 2, 50);
        addItem(victoryImage);
    }
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

