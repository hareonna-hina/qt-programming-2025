#include "Knife.h"
#include "../Items/Characters/Character.h"

Knife::Knife(QGraphicsItem* parent)
    :Weapon(parent,":/Items/Armors/FlamebreakerArmor/knife.png",KNIFE)
{
    setVisible(true);
}

void Knife::attack(Character* user)
{
    Weapon::attack(user);

    if(facingRight)
    {
        setPos(40,0);
    }
    else
    {
        setPos(-40,0);
    }
    // 检查攻击范围内是否有敌人
    QList<QGraphicsItem*> items = scene()->items();
    QRectF attackArea = boundingRect().translated(pos());

    for (QGraphicsItem* item : items)
    {
        if (auto enemy = dynamic_cast<Character*>(item))
        {
            if (enemy != user && enemy->collidesWithItem(this))
            {
                enemy->takeDamage(20); // 小刀伤害
            }
        }
    }
}

QRectF Knife::boundingRect() const
{
    // 返回刀具的碰撞边界（基于加载的图像）
    if (!weaponPixmap.isNull())
    {
        return QRectF(0, 0, weaponPixmap.width(), weaponPixmap.height());
    }
    return QRectF(0, 0, 30, 10); // 默认大小（如果图像加载失败）
}

// 实现 paint() 函数
void Knife::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // 绘制刀具图像
    if (!weaponPixmap.isNull())
    {
        if (facingRight)
        {
            painter->drawPixmap(0, 0, weaponPixmap);
        }
        else
        {
            // 镜像绘制（如果角色面向左侧）
            painter->save();
            painter->translate(weaponPixmap.width(), 0);
            painter->scale(-1, 1);
            painter->drawPixmap(0, 0, weaponPixmap);
            painter->restore();
        }
    }
}
