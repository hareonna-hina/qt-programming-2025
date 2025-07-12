#include "Rifle.h"
#include "Bullet.h"
#include "../Items/Characters/Character.h"
#include <QDateTime>

Rifle::Rifle(QGraphicsItem* parent)
    : Weapon(parent, ":/Items/Armors/FlamebreakerArmor/gun.png", RIFLE)
{
    // 步枪不需要隐藏
    setVisible(true);
}

void Rifle::attack(Character* user)
{
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();

    // 检查射击间隔
    if (currentTime - lastFireTime < FIRE_INTERVAL)
    {
        return;
    }

    if (bulletCount > 0)
    {

        // 设置位置 - 在人物前方
        if (facingRight)
        {
            setPos(40, 20); // 人物右侧
        }
        else
        {
            setPos(-40, 20); // 人物左侧
        }

        // 创建子弹
        Bullet* bullet = new Bullet(user->pos(), facingRight, 10.0); // 子弹速度
        user->scene()->addItem(bullet);

        bulletCount--;
        lastFireTime = currentTime;

        if (bulletCount <= 0)
        {
            // 子弹用完，丢弃武器
            user->setCurrentWeapon(user->getFist());
        }
    } else {
        // 没有子弹，自动切换到拳头
        user->setCurrentWeapon(user->getFist());
        user->attack(); // 使用拳头攻击
    }
}
