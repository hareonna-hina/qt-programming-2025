#ifndef SNIPER_H
#define SNIPER_H
#include "Weapon.h"

class Sniper : public Weapon
{
public:
    explicit Sniper(QGraphicsItem* parent);
    void attack(Character* user) override;

private:
    int bulletCount = 3; // 子弹数量
    qint64 lastFireTime = 0; // 上次射击时间
    const qint64 FIRE_INTERVAL = 1000; // 射击间隔(毫秒)
};

#endif // SNIPER_H
