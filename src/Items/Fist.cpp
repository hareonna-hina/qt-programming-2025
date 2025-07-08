#include "Fist.h"
#include "../Items/Characters/Character.h"

Fist::Fist(QGraphicsItem* parent)
    :Weapon(parent,":/Items/Armors/FlamebreakerArmor/fist.png",FIST)
{
    setVisible(false);
}

void Fist::attack(Character* user)
{
    Weapon::attack(user);

    if(facingRight)
    {
        setPos(32,16);
    }
    else
    {
        setPos(-32,16);
    }
    // 检查攻击范围内是否有敌人
    QList<QGraphicsItem*> items = scene()->items();
    QRectF attackArea = boundingRect().translated(pos());

    // 如果面向左边，调整攻击区域
    if (!facingRight)
    {
        attackArea.setX(pos().x() - attackArea.width());
    }

    for (QGraphicsItem* item : items)
    {
        if (auto enemy = dynamic_cast<Character*>(item))
        {
            if (enemy != user && enemy->collidesWithItem(this))
            {
                enemy->takeDamage(10); // 拳头伤害
            }
        }
    }
}
