//
// Created by gerw on 8/20/24.
//

#ifndef QT_PROGRAMMING_2024_CHARACTER_H
#define QT_PROGRAMMING_2024_CHARACTER_H

#include <QGraphicsEllipseItem>
#include "../HeadEquipments/HeadEquipment.h"
#include "../Armors/Armor.h"
#include "../LegEquipments/LegEquipment.h"


class Character : public Item {
public:
    // 添加角色类型标识
    enum CharacterType { TYPE_PLAYER1, TYPE_PLAYER2 };

    explicit Character(CharacterType type, QGraphicsItem *parent); // 修改构造函数

    [[nodiscard]] bool isLeftDown() const;

    void setLeftDown(bool leftDown);

    [[nodiscard]] bool isRightDown() const;

    void setRightDown(bool rightDown);

    [[nodiscard]] bool isPickDown() const;

    void setPickDown(bool pickDown);

    [[nodiscard]] const QPointF &getVelocity() const;

    [[nodiscard]] bool isPicking() const;

    void setVelocity(const QPointF &velocity);

    void processInput();

    Armor* pickupArmor(Armor* newArmor);

    CharacterType characterType() const { return m_type; } // 获取角色类型

protected:
    HeadEquipment *headEquipment{};
    LegEquipment *legEquipment{};
    Armor *armor{};
    QPointF velocity{};
    CharacterType m_type; // 存储角色类型
//    QGraphicsEllipseItem *ellipseItem; // for debugging
private:
    bool leftDown{}, rightDown{}, pickDown{};
    bool lastPickDown{};
    bool picking{};
};


#endif //QT_PROGRAMMING_2024_CHARACTER_H
