//
// Created by gerw on 8/20/24.
//

#include <QTransform>
#include "Character.h"

Character::Character(CharacterType type, QGraphicsItem *parent)
    : Item(parent, ""), m_type(type),is_squating(false) {
    if(type==TYPE_PLAYER1)
    {
        // 加载静止状态的图片
        idlePixmapItem = new QGraphicsPixmapItem(QPixmap(":/Items/Armors/FlamebreakerArmor/character_beige_idle.png"), this);
        idlePixmapItem->setPos(0, 0);
        idlePixmapItem->setVisible(true);

        // 加载移动状态的图片
        movingPixmapItem = new QGraphicsPixmapItem(QPixmap(":/Items/Armors/FlamebreakerArmor/character_beige_walk.png"), this);
        movingPixmapItem->setPos(0, 0);
        movingPixmapItem->setVisible(false);

        // 加载跳跃状态的图片
        jumpingPixmapItem = new QGraphicsPixmapItem(QPixmap(":/Items/Armors/FlamebreakerArmor/character_beige_jump.png"), this);
        jumpingPixmapItem->setPos(0, 0);
        jumpingPixmapItem->setVisible(false);

        // 加载下蹲状态的图片
        squatingPixmapItem = new QGraphicsPixmapItem(QPixmap(":/Items/Armors/FlamebreakerArmor/character_beige_squat.png"), this);
        squatingPixmapItem->setPos(0, 0);
        squatingPixmapItem->setVisible(false);
    }
    if (type==TYPE_PLAYER2)
    {
        // 加载静止状态的图片
        idlePixmapItem = new QGraphicsPixmapItem(QPixmap(":/Items/Armors/FlamebreakerArmor/character_green_idle.png"), this);
        idlePixmapItem->setPos(0, 0);
        idlePixmapItem->setVisible(true);

        // 加载移动状态的图片
        movingPixmapItem = new QGraphicsPixmapItem(QPixmap(":/Items/Armors/FlamebreakerArmor/character_green_walk.png"), this);
        movingPixmapItem->setPos(0, 0);
        movingPixmapItem->setVisible(false);

        // 加载跳跃状态的图片
        jumpingPixmapItem = new QGraphicsPixmapItem(QPixmap(":/Items/Armors/FlamebreakerArmor/character_green_jump.png"), this);
        jumpingPixmapItem->setPos(0, 0);
        jumpingPixmapItem->setVisible(false);

        // 加载下蹲状态的图片
        squatingPixmapItem = new QGraphicsPixmapItem(QPixmap(":/Items/Armors/FlamebreakerArmor/character_green_squat.png"), this);
        squatingPixmapItem->setPos(0, 0);
        squatingPixmapItem->setVisible(false);
    }
//    ellipseItem = new QGraphicsEllipseItem(-5, -5, 10, 10, this);
//    // Optionally, set some properties of the ellipse
//    ellipseItem->setBrush(Qt::green);          // Fill color
//    ellipseItem->setZValue(1);

}


bool Character::isLeftDown() const {
    return leftDown;
}

void Character::setLeftDown(bool leftDown) {
    Character::leftDown = leftDown;
}

bool Character::isRightDown() const {
    return rightDown;
}

void Character::setRightDown(bool rightDown) {
    Character::rightDown = rightDown;
}

bool Character::isPickDown() const {
    return pickDown;
}

void Character::setPickDown(bool pickDown) {
    Character::pickDown = pickDown;
}


void Character::setJumpDown(bool jumpDown) {
    Character::jumpDown = jumpDown;
}
bool Character::isJumpDown() const {
    return jumpDown;
}

void Character::setSquatDown(bool squatDown) {
    Character::squatDown = squatDown;
}
bool Character::isSquatDown() const {
    return squatDown;
}

const QPointF &Character::getVelocity() const {
    return velocity;
}

void Character::setVelocity(const QPointF &velocity) {
    Character::velocity = velocity;
}

void Character::processInput() {
    auto velocity = QPointF(0, 0);
    const auto moveSpeed = 0.3;

    // 根据角色类型分配不同按键
    if (m_type == TYPE_PLAYER1) {
        if (isLeftDown()) {  // 玩家1向左移动
            velocity.setX(velocity.x() - moveSpeed);
            setTransform(QTransform().scale(-1, 1));
            //setVelocity(velocity);
        }
        if (isRightDown()) { // 玩家1向右移动
            velocity.setX(velocity.x() + moveSpeed);
            setTransform(QTransform().scale(1, 1));
            //setVelocity(velocity);
        }
        // 添加玩家1其他按键控制...
    } else { // 玩家2控制
        if (isLeftDown()) {  // 玩家2向左移动
            velocity.setX(velocity.x() - moveSpeed);
            setTransform(QTransform().scale(-1, 1));
            //setVelocity(velocity);
        }
        if (isRightDown()) { // 玩家2向右移动
            velocity.setX(velocity.x() + moveSpeed);
            setTransform(QTransform().scale(1, 1));
            //setVelocity(velocity);
        }
        // 添加玩家2其他按键控制...
    }
    setVelocity(velocity);


    if (!lastPickDown && pickDown)
    { // first time pickDown
        picking = true;
    }
    else
    {
        picking = false;
    }
    lastPickDown = pickDown;

    // 根据速度更新人物状态
    qDebug()<<"squat:"<<is_squating;
    if(is_squating)
    {
        setState(STATE_SQUATING);
        qDebug()<<"3";
    }
    else if((velocity.x()!=0||velocity.y()!=0)&&!is_squating)
    {
        setState(STATE_MOVING);
        qDebug()<<"1";
    }
    else
    {
        setState(STATE_IDLE);
        qDebug()<<"2";
        qDebug()<<"squat:"<<is_squating;
    }
    update();

}

bool Character::isPicking() const {
    return picking;
}

// Armor *Character::pickupArmor(Armor *newArmor) {
//     auto oldArmor = armor;
//     if (oldArmor != nullptr) {
//         oldArmor->unmount();
//         oldArmor->setPos(newArmor->pos());
//         oldArmor->setParentItem(parentItem());
//     }
//     newArmor->setParentItem(this);
//     newArmor->mountToParent(this);
//     armor = newArmor;
//     return oldArmor;
// }

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (m_state == STATE_IDLE)
    {
        idlePixmapItem->setVisible(true);
        movingPixmapItem->setVisible(false);
        jumpingPixmapItem->setVisible(false);
        squatingPixmapItem->setVisible(false);
    }
    else if (m_state == STATE_MOVING)
    {
        idlePixmapItem->setVisible(false);
        movingPixmapItem->setVisible(true);
        jumpingPixmapItem->setVisible(false);
        squatingPixmapItem->setVisible(false);
    }
    else if (m_state == STATE_JUMPING)
    {
        idlePixmapItem->setVisible(false);
        movingPixmapItem->setVisible(false);
        jumpingPixmapItem->setVisible(true);
        squatingPixmapItem->setVisible(false);
    }
    else if (m_state == STATE_SQUATING)
    {
        idlePixmapItem->setVisible(false);
        movingPixmapItem->setVisible(false);
        jumpingPixmapItem->setVisible(false);
        squatingPixmapItem->setVisible(true);
    }

    if (idlePixmapItem->isVisible())
    {
        idlePixmapItem->paint(painter, option, widget);
    }
    if (movingPixmapItem->isVisible())
    {
        movingPixmapItem->paint(painter, option, widget);
    }
    if (jumpingPixmapItem->isVisible())
    {
        jumpingPixmapItem->paint(painter, option, widget);
    }
    if (squatingPixmapItem->isVisible())
    {
        squatingPixmapItem->paint(painter, option, widget);
    }
    update();
}


