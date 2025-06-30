//
// Created by gerw on 8/20/24.
//

#include <QTransform>
#include "Character.h"

Character::Character(CharacterType type, QGraphicsItem *parent)
    : Item(parent, ""), m_type(type) {
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
            setTransform(QTransform().scale(1, 1));
        }
        if (isRightDown()) { // 玩家1向右移动
            velocity.setX(velocity.x() + moveSpeed);
            setTransform(QTransform().scale(-1, 1));
        }
        // 添加玩家1其他按键控制...
    } else { // 玩家2控制
        if (isLeftDown()) {  // 玩家2向左移动
            velocity.setX(velocity.x() - moveSpeed);
            setTransform(QTransform().scale(1, 1));
        }
        if (isRightDown()) { // 玩家2向右移动
            velocity.setX(velocity.x() + moveSpeed);
            setTransform(QTransform().scale(-1, 1));
        }
        // 添加玩家2其他按键控制...
    }

    setVelocity(velocity);

    if (!lastPickDown && pickDown) { // first time pickDown
        picking = true;
    } else {
        picking = false;
    }
    lastPickDown = pickDown;
}

bool Character::isPicking() const {
    return picking;
}

Armor *Character::pickupArmor(Armor *newArmor) {
    auto oldArmor = armor;
    if (oldArmor != nullptr) {
        oldArmor->unmount();
        oldArmor->setPos(newArmor->pos());
        oldArmor->setParentItem(parentItem());
    }
    newArmor->setParentItem(this);
    newArmor->mountToParent(this);
    armor = newArmor;
    return oldArmor;
}


