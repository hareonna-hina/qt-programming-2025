//
// Created by gerw on 8/20/24.
//

#include <QTransform>
#include "Character.h"
#include <QDateTime>
#include <QKeyEvent>
#include "../Fist.h"
#include "../Knife.h"
#include "../Bullet.h"
#include "../Rifle.h"
#include "../Sniper.h"
#include "../SolidBall.h"
#include "../Projectile.h"
#include <QDebug>


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

        //下蹲时的隐身
        invisiblePixmapItem = new QGraphicsPixmapItem(QPixmap(":/Items/Armors/FlamebreakerArmor/character_beige_invisible.png"), this);
        invisiblePixmapItem->setPos(0, 0);
        invisiblePixmapItem->setVisible(false);
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

        // 加载隐身状态的图片
        invisiblePixmapItem = new QGraphicsPixmapItem(QPixmap(":/Items/Armors/FlamebreakerArmor/character_green_invisible.png"), this);
        invisiblePixmapItem->setPos(0, 0);
        invisiblePixmapItem->setVisible(false);
    }

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

void Character::setAttackDown(bool attackDown)
{
    Character::attackDown=attackDown;
}
bool Character::isAttackDown() const
{
    return attackDown;
}

const QPointF &Character::getVelocity() const {
    return velocity;
}

void Character::setVelocity(const QPointF &velocity) {
    Character::velocity = velocity;
}

void Character::processInput() {
    auto velocity = QPointF(0, 0);
    const auto speed = 0.3;
    auto moveSpeed=0.0;
    if(is_accelerating)
    {
        moveSpeed=speed+0.2;
    }
    else
    {
        moveSpeed=speed;
    }
    // 根据角色类型分配不同按键
    if (m_type == TYPE_PLAYER1)
    {
        if (isLeftDown())
        {  // 玩家1向左移动
            velocity.setX(velocity.x() - moveSpeed);
            setTransform(QTransform().scale(-1, 1));
            m_isFacingRight=false;
        }
        if (isRightDown())
        { // 玩家1向右移动
            velocity.setX(velocity.x() + moveSpeed);
            setTransform(QTransform().scale(1, 1));
            m_isFacingRight=true;
        }
        if(isJumpDown()&&!is_jumping)
        {
            velocity.setY(JUMPING_SPEED);
        }
        // 添加玩家1其他按键控制...
    }
    else
    { // 玩家2控制
        if (isLeftDown())
        {  // 玩家2向左移动
            velocity.setX(velocity.x() - moveSpeed);
            setTransform(QTransform().scale(-1, 1));
            m_isFacingRight=false;
        }
        if (isRightDown())
        { // 玩家2向右移动
            velocity.setX(velocity.x() + moveSpeed);
            setTransform(QTransform().scale(1, 1));
            m_isFacingRight=true;
        }
        if(isJumpDown()&&!is_jumping)
        {
            velocity.setY(JUMPING_SPEED);
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
    if(picking)
    {
        processPicking();
    }

    // 根据速度更新人物状态
    if(is_squating)
    {
        if(!first_set_y)
        {
            first_set_y=true;
            setPos(x(),y()+16);
        }
        setState(STATE_SQUATING);
    }
    else if(velocity.y()!=0&&!is_squating)
    {
        if(m_state==STATE_SQUATING)
        {
            setPos(x(),y()-16);
            first_set_y=false;
        }
        setState(STATE_JUMPING);
    }
    else if((velocity.x()!=0&&velocity.y()==0)&&!is_squating)
    {
        if(m_state==STATE_SQUATING)
        {
            setPos(x(),y()-16);
            first_set_y=false;
        }
        setState(STATE_MOVING);
    }
    else if(velocity.x()==0&&velocity.y()==0)
    {
        if(m_state==STATE_SQUATING)
        {
            setPos(x(),y()-16);
            first_set_y=false;
        }
        setState(STATE_IDLE);
    }
    update();

}

void Character::processPicking()
{
    if (!isPicking() || !isAlive()) return;

    QList<QGraphicsItem*> sceneItems = scene()->items();
    for (QGraphicsItem* item : sceneItems)
    {
        Weapon* weapon = dynamic_cast<Weapon*>(item);
        if (weapon && weapon->parentItem() == nullptr)
        {
            QRectF charWorldRect = mapToScene(collisionRect()).boundingRect();
            QRectF weaponWorldRect = weapon->mapToScene(weapon->boundingRect()).boundingRect();
            if (!charWorldRect.intersects(weaponWorldRect)) continue;

            QRectF charLocalRect = collisionRect(); // 人物碰撞盒（局部坐标）
            QRectF weaponLocalRect = weapon->boundingRect(); // 武器碰撞盒（局部坐标）
            weapon->setParentItem(this);
            setCurrentWeapon(weapon);
            if(m_currentWeaponType==SNIPER)
            {
                qreal offsetX = isFacingRight()
                ? (charLocalRect.width() - weaponLocalRect.width()+30)
                : weaponLocalRect.width();
                qreal offsetY = (charLocalRect.height() - weaponLocalRect.height()+14) / 2;//这个+14和+10是调出来的，保证武器在人物手上
                weapon->setPos(offsetX, offsetY);
            }
            else
            {
                qreal offsetX = isFacingRight()
                ? (charLocalRect.width() - weaponLocalRect.width()+14)
                : weaponLocalRect.width()+30;
                qreal offsetY = (charLocalRect.height() - weaponLocalRect.height()+10) / 2;//这个+14和+10是调出来的，保证武器在人物手上
                weapon->setPos(offsetX, offsetY);
            }
            return;
        }
    }
}

bool Character::isPicking() const {
    return picking;
}


void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (m_state == STATE_IDLE)
    {
        idlePixmapItem->setVisible(true);
        movingPixmapItem->setVisible(false);
        jumpingPixmapItem->setVisible(false);
        squatingPixmapItem->setVisible(false);
        invisiblePixmapItem->setVisible(false);
    }
    else if (m_state == STATE_MOVING)
    {
        idlePixmapItem->setVisible(false);
        movingPixmapItem->setVisible(true);
        jumpingPixmapItem->setVisible(false);
        squatingPixmapItem->setVisible(false);
        invisiblePixmapItem->setVisible(false);
    }
    else if (m_state == STATE_JUMPING)
    {
        idlePixmapItem->setVisible(false);
        movingPixmapItem->setVisible(false);
        jumpingPixmapItem->setVisible(true);
        squatingPixmapItem->setVisible(false);
        invisiblePixmapItem->setVisible(false);
    }
    else if (m_state == STATE_SQUATING)
    {
        idlePixmapItem->setVisible(false);
        movingPixmapItem->setVisible(false);
        jumpingPixmapItem->setVisible(false);
        if(!is_set_invisible)
        {
            squatingPixmapItem->setVisible(true);
            invisiblePixmapItem->setVisible(false);
        }
        else
        {
            squatingPixmapItem->setVisible(false);
            invisiblePixmapItem->setVisible(true);
        }

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
    if (invisiblePixmapItem->isVisible())
    {
        invisiblePixmapItem->paint(painter, option, widget);
    }
    update();
}

void Character::applyGravity(qreal deltaTime)
{
    if(!m_isGrounded)
    {
        airTime+=0.025;
        velocity.setY(velocity.y()+GRAVITY*airTime);
        if(velocity.y()>=MAX_FALL_SPEED)
        {
            velocity.setY(MAX_FALL_SPEED);
        }
    }
    else
    {
        velocity.setY(0);
        airTime=0;
        is_jumping=false;
    }
    setY(y()+velocity.y()*airTime);
    update();
}

QRectF Character::collisionRect() const
{
    return QRectF(0,0,COLLISION_SIZE,COLLISION_SIZE);
}

QRectF Character::boundingRect() const
{
    return QRectF(0,0,COLLISION_SIZE,COLLISION_SIZE);
}

void Character::checkCollisions(Map* map)
{
    if(!map)
        return;
    QRectF charRect=collisionRect().translated(pos());
    qreal groundY=map->getFloorHeightAt(charRect.center().x());
    if(charRect.bottom()>=groundY)
    {
        setY(groundY-COLLISION_SIZE);
        m_isGrounded=true;
        velocity.setY(0);
    }
    else
    {
        m_isGrounded=false;
    }

    qreal ceilingY=map->getCeilingHeight();
    if(charRect.top()<=ceilingY-20)
    {
        setY(ceilingY);
        velocity.setY(0);
    }

    if(m_isGrounded)
    {
        QRectF probeRect(charRect.center().x()-5,
                         charRect.bottom(),
                         10,
                         10);

        if(!map->isSolidAt(probeRect))
        {
            m_isGrounded=false;
        }
    }

    qreal mapLeft=0;
    qreal mapRight=1280;

    if (charRect.left() <= mapLeft+charRect.width())
    {
        setX(charRect.width());
        velocity.setX(0); // 停止水平移动
    }
    // 右侧边界检测
    if (charRect.right() > mapRight)
    {
        setX(1280 - charRect.width());
        velocity.setX(0); // 停止水平移动
    }

    //游戏里的地形障碍设置
    if(charRect.right()>=190&&charRect.right()<=300&&qAbs(charRect.bottom()-504)<0.1&&qAbs(charRect.top()-440)<0.1)//地图左边第一个台阶的水平检测
    {
        setX(128);
        velocity.setX(0);
    }
    if(charRect.left()<=1218&&charRect.left()>=1128&&qAbs(charRect.bottom()-504)<0.1&&qAbs(charRect.top()-440)<0.1)//地图右边第一个台阶的水平检测
    {
        setX(1218);
        velocity.setX(0);
    }

    if(charRect.right()>=254&&charRect.right()<=364&&charRect.bottom()>=440&&velocity.y()>=0)//地图左边第二个台阶
    {
        setX(192);
        setY(376);
        velocity.setX(0);
        velocity.setY(0);
        m_isGrounded=true;
    }
    if(charRect.left()<=1154&&charRect.left()>=1064&&charRect.bottom()>=440&&velocity.y()>=0)//地图右边第二个台阶
    {
        setX(1154);
        setY(376);
        velocity.setX(0);
        velocity.setY(0);
        m_isGrounded=true;
    }

    if(charRect.right()>=316&&charRect.right()<=428&&charRect.bottom()>=376&&velocity.y()>=0)//地图左边第3个台阶
    {
        setX(256);
        setY(312);
        velocity.setX(0);
        velocity.setY(0);
        m_isGrounded=true;
    }
    if(charRect.left()<=1090&&charRect.left()>=1000&&charRect.bottom()>=376&&velocity.y()>=0)//地图右边第3个台阶
    {
        setX(1090);
        setY(312);
        velocity.setX(0);
        velocity.setY(0);
        m_isGrounded=true;
    }

    if(charRect.right()>=380&&charRect.right()<=500&&charRect.bottom()>=312&&velocity.y()>=0)//地图左边第3个台阶上方
    {
        setY(251);
        velocity.setY(0);
        m_isGrounded=true;
    }
    if(charRect.left()<=1036&&charRect.left()>=900&&charRect.bottom()>=312&&velocity.y()>=0)//地图右边第3个台阶上方
    {
        setY(251);
        velocity.setY(0);
        m_isGrounded=true;
    }

    if(charRect.left()>=100&&charRect.right()<=347&&charRect.bottom()<=220&&charRect.bottom()>=215&&velocity.y()>=0)//左侧浮空平台上方
    {
        setY(155);
        velocity.setY(0);
        m_isGrounded=true;
    }
    if(charRect.left()>=1036&&charRect.right()<=1280&&charRect.bottom()<=220&&charRect.bottom()>=215&&velocity.y()>=0)//右侧浮空平台上方
    {
        setY(155);
        velocity.setY(0);
        m_isGrounded=true;
    }

    if(charRect.left()>=350&&charRect.right()<=1050&&charRect.bottom()>=30&&charRect.bottom()<=130)//最上方平台
    {
        setY(42);
        velocity.setY(0);
        m_isGrounded=true;
    }


}

void Character::differentTerrain(Map* map)
{
    if(!map) return;
    QRectF charRect=collisionRect().translated(pos());
    if((charRect.left()>=159&&charRect.right()<=428&&charRect.bottom()>=200&&charRect.bottom()<=440)
        ||(charRect.left()<=1154&&charRect.left()>=900&&charRect.bottom()>=200&&charRect.bottom()<=440))//雪地加速
    {
        is_set_invisible=false;
        if(!is_accelerating)
        {
            is_accelerating=true;
        }
    }
    else if((charRect.left()>=0&&charRect.left()<=159&&qAbs(charRect.top()-440)<5)||
               (charRect.left()<=1280&&charRect.left()>=1128&&qAbs(charRect.top()-440)<5)
               ||(charRect.left()>=350&&charRect.right()<=1050&&charRect.bottom()>=30&&charRect.bottom()<=130))//草地下蹲隐身
    {
        is_set_invisible=true;
        is_accelerating=false;
    }
    else//土地啥也没有
    {
        is_set_invisible=false;
        is_accelerating=false;
    }
    update();
}

void Character::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;

    // 更新生命值显示
    updateHealthDisplay();

    if (health <= 0) {
        // 隐藏角色
        setVisible(false);
        // 通知场景玩家死亡
        if (scene()) {
            scene()->update();
        }
    }
}

void Character::updateHealthDisplay()
{
    if (statusBar)
    {
        statusBar->updateHearts(health);
    }
}

// void Character::checkProjectileCollisions()
// {
//     if (!scene() || !isAlive()) return;

//     // 获取所有投射物
//     QList<QGraphicsItem*> items = scene()->items();
//     QRectF charRect = collisionRect().translated(pos());

//     for (QGraphicsItem* item : items)
//     {
//         if (auto bullet = dynamic_cast<Bullet*>(item))
//         {
//             // 检查子弹是否击中
//             QRectF bulletRect = bullet->boundingRect().translated(bullet->pos());
//             if (charRect.intersects(bulletRect))
//             {
//                 takeDamage(bullet->getDamage());
//                 scene()->removeItem(item);
//                 delete item;
//             }
//         }
//         else if (auto projectile = dynamic_cast<Projectile*>(item))
//         {
//             // 检查投掷物是否击中
//             QRectF projRect = projectile->boundingRect().translated(projectile->pos());
//             if (charRect.intersects(projRect))
//             {
//                 takeDamage(projectile->getDamage());
//                 scene()->removeItem(item);
//                 delete item;
//             }
//         }
//         else if (dynamic_cast<Knife*>(item) || dynamic_cast<Fist*>(item))
//         {
//             // 近战武器碰撞检测
//             if (item->isVisible())
//             { // 只在攻击时检测
//                 QRectF weaponRect = item->boundingRect().translated(item->pos());
//                 if (charRect.intersects(weaponRect))
//                 {
//                     Character* attacker = dynamic_cast<Character*>(item->parentItem());
//                     if (attacker && attacker != this)
//                     {
//                         Weapon* weapon = dynamic_cast<Weapon*>(item);
//                         if (weapon)
//                         {
//                             weapon->attack(this);
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }

void Character::setCurrentWeapon(Weapon* weapon)
{
    // 移除旧武器（仅解除父子关系，不删除，允许丢弃在场景）
    if (currentWeapon && currentWeapon != fist)
    { // 保留拳头作为默认武器
        currentWeapon->setParentItem(nullptr); // 旧武器脱离角色
        currentWeapon->setVisible(true); // 旧武器显示在场景中（可被再次拾取）
        currentWeapon->setPos(x(),y());
    }

    // 设置新武器
    currentWeapon = weapon;
    if (currentWeapon)
    {
        currentWeapon->setParentItem(this); // 新武器跟随角色
        currentWeapon->setFacingRight(transform().m11() > 0); // 同步朝向
        currentWeapon->setVisible(true);
    }
    else
    {
        // 若新武器为空，默认使用拳头
        currentWeapon = fist;
        currentWeapon->setParentItem(this);
    }
    m_currentWeaponType=currentWeapon->getType();
}

void Character::attack()
{
    if (currentWeapon && isAlive())
    {
        currentWeapon->setFacingRight(transform().m11() > 0); // 攻击时同步朝向
        currentWeapon->attack(this);
    }
}

