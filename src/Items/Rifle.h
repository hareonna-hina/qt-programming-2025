#ifndef RIFLE_H
#define RIFLE_H


#include "Weapon.h"

class Rifle : public Weapon
{
public:
    explicit Rifle(QGraphicsItem* parent);
    void attack(Character* user) override;

private:
    int bulletCount = 10;
    qint64 lastFireTime = 0; // 上次射击时间
    const qint64 FIRE_INTERVAL = 200; // 射击间隔(毫秒)
};
#endif // RIFLE_H
