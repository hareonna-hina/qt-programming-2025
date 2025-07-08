#include "Sniper.h"
#include "Bullet.h"
#include <QDateTime>
#include "../Items/Characters/Character.h"
#include <QDebug>

Sniper::Sniper(QGraphicsItem* parent)
    : Weapon(parent, "::/Items/Armors/FlamebreakerArmor/sniper.png", SNIPER)
{
    setVisible(true);
}

void Sniper::attack(Character* user)
{
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();

    // 检查射击间隔
    if (currentTime - lastFireTime < FIRE_INTERVAL)
    {
        return;
    }

    if (bulletCount > 0)
    {
        Weapon::attack(user);

        // 设置位置 - 在人物前方
        if (facingRight)
        {
            setPos(50, 15); // 人物右侧
        }
        else
        {
            setPos(-50, 15); // 人物左侧
        }

        // 创建子弹（高伤害）
        Bullet* bullet = new Bullet(user->pos(), facingRight, 20.0, 50); // 高速子弹，高伤害
        user->scene()->addItem(bullet);

        bulletCount--;
        lastFireTime = currentTime;

        if (bulletCount <= 0)
        {
            // 子弹用完，丢弃武器
            user->setCurrentWeapon(user->getFist());
        }
    }
    else
    {
        // 没有子弹，自动切换到拳头
        user->setCurrentWeapon(user->getFist());
        user->attack(); // 使用拳头攻击
    }
}
