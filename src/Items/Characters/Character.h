//
// Created by gerw on 8/20/24.
//

#ifndef QT_PROGRAMMING_2024_CHARACTER_H
#define QT_PROGRAMMING_2024_CHARACTER_H

#include <QGraphicsEllipseItem>
#include "../HeadEquipments/HeadEquipment.h"
#include "../Armors/Armor.h"
#include "../LegEquipments/LegEquipment.h"
#include <QGraphicsPixmapItem>
#include <QPointF>
#include "../Maps/Map.h"
#include "../Weapon.h"
#include "../StatusBar.h"


class Character : public Item {
public:
    // 添加角色类型标识
    enum CharacterType { TYPE_PLAYER1, TYPE_PLAYER2 };
    // 添加人物状态枚举
    enum CharacterState { STATE_IDLE, STATE_MOVING ,STATE_JUMPING,STATE_SQUATING};

    explicit Character(CharacterType type, QGraphicsItem *parent); // 修改构造函数

    [[nodiscard]] bool isLeftDown() const;
    void setLeftDown(bool leftDown);

    [[nodiscard]] bool isRightDown() const;
    void setRightDown(bool rightDown);

    [[nodiscard]] bool isPickDown() const;
    void setPickDown(bool pickDown);

    [[nodiscard]] bool isJumpDown() const;
    void setJumpDown(bool jumpDown);

    [[nodiscard]] bool isSquatDown() const;
    void setSquatDown(bool squatDown);

    [[nodiscard]] const QPointF &getVelocity() const;

    [[nodiscard]] bool isPicking() const;
    void processPicking();

    void setVelocity(const QPointF &velocity);

    void processInput();

    Armor* pickupArmor(Armor* newArmor);

    CharacterType characterType() const { return m_type; } // 获取角色类型

    void addEquipmentCard(Equipment *equipment);

    void removeEquipmentCard(Equipment *equipment); // 把装备加入到装备槽中，减少人物绘图的复杂，让界面更简洁

    void checkCollisions(Map* map);
    QRectF collisionRect() const;
    void applyGravity(qreal deltaTime);

    // 获取和设置人物状态的方法
    CharacterState getState() const { return m_state; }
    void setState(CharacterState state) { m_state = state; }

    qreal m_squatStartTime=0;
    bool is_squating;
    bool first_set_y=false;
    bool is_set_invisible=false;

    const qint64 JITTER_THRESHOLD = 50;  // 50ms抖动阈值

    bool getOnGround(){return m_isGrounded;};

    bool is_jumping=false;

    void differentTerrain(Map* map);

    // 生命值相关
    [[nodiscard]] int getHealth() const { return health; }
    void takeDamage(int amount);
    bool isAlive() const { return health > 0; }
    void updateHealthDisplay();

    // 获取状态栏引用
    void setStatusBar(StatusBar* bar) { statusBar = bar; }

    // 武器相关方法
    void setCurrentWeapon(Weapon* weapon);
    Weapon* getCurrentWeapon() const { return currentWeapon; }
    Weapon* getFist() const { return fist; }
    void attack();

    // 添加攻击键状态
    [[nodiscard]] bool isAttackDown() const;
    void setAttackDown(bool attackDown);

    // 碰撞检测
    void checkProjectileCollisions();
    bool isFacingRight(){return m_isFacingRight;}

    WeaponType getCurrentWeaponType() const {return m_currentWeaponType;}

protected:
    Armor *armor{};
    QPointF velocity{};
    CharacterType m_type; // 存储角色类型
    QList<Equipment*> equipmentCards;
    // 用于存储不同状态的图片项
    QGraphicsPixmapItem *idlePixmapItem;
    QGraphicsPixmapItem *movingPixmapItem;
    QGraphicsPixmapItem *jumpingPixmapItem;
    QGraphicsPixmapItem *squatingPixmapItem;
    QGraphicsPixmapItem *invisiblePixmapItem;
    // 当前人物状态
    CharacterState m_state;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    // 武器成员
    Weapon* currentWeapon = nullptr;
    Weapon* fist = nullptr;  // 默认武器（拳头）

    // 攻击键状态
    bool attackDown{};

    // 生命值
    int health = 100;
    int maxHealth = 100;

    // 状态栏
    StatusBar* statusBar = nullptr;

private:
    bool leftDown{}, rightDown{}, pickDown{};
    bool lastPickDown{};
    bool picking{};
    bool jumpDown{},squatDown{};
    bool m_isGrounded=false;
    const qreal GRAVITY=5;
    const qreal MAX_FALL_SPEED=10;
    const int COLLISION_SIZE=64;
    const qreal JUMPING_SPEED=-0.4;//初始跳跃速度
    qreal airTime=0;
    bool is_accelerating=false;
    bool m_isFacingRight=true;
    WeaponType m_currentWeaponType=FIST;


};


#endif //QT_PROGRAMMING_2024_CHARACTER_H
