#include "SolidBall.h"
#include "Projectile.h"
#include "../Items/Characters/Character.h"

SolidBall::SolidBall(QGraphicsItem* parent)
    :Weapon(parent,":/Items/Armors/FlamebreakerArmor/solidball.png",SOLID_BALL)
{
    setVisible(true);
}

void SolidBall::attack(Character* user)
{
    if (throwCount > 0)
    {

        // 设置位置 - 在人物前方
        if (facingRight)
        {
            setPos(30, 10); // 人物右前方
        }
        else
        {
            setPos(-30, 10); // 人物左前方
        }

        // 创建投掷物
        Projectile* ball = new Projectile(user->pos(), facingRight, 5.0, 15.0); // 初始速度和角度
        user->scene()->addItem(ball);

        throwCount--;

        if (throwCount <= 0)
        {
            // 投掷次数用完，丢弃武器
            user->setCurrentWeapon(user->getFist());
            qDebug() << "实心球用完，切换回拳头";
        }
    }
    else
    {
        // 没有投掷次数，自动切换到拳头
        user->setCurrentWeapon(user->getFist());
        user->attack(); // 使用拳头攻击
    }
}
