#include "Fist.h"
#include "../Items/Characters/Character.h"

Fist::Fist(QGraphicsItem* parent)
    :Weapon(parent,":/Items/Armors/FlamebreakerArmor/fist.png",FIST)
{
    setVisible(false);
}

void Fist::attack(Character* user)
{
    qDebug()<<1;
    setVisible(true);
    facingRight = (user->transform().m11() > 0);

    // 根据朝向调整位置（确保图片与角色对齐）
    if (facingRight)
    {
        setPos(32, 16);  // 角色右侧
    }
    else
    {
        setPos(-32, 16); // 角色左侧
    }

    // 执行碰撞检测（使用图片原始大小）
    QRectF attackArea = mapToScene(boundingRect()).boundingRect();
    QList<QGraphicsItem*> items = user->scene()->items(attackArea);

    for (QGraphicsItem* item : items)
    {
        if (auto enemy = dynamic_cast<Character*>(item))
        {
            if (enemy != user)
            {
                enemy->takeDamage(10);
            }
        }
    }
}
