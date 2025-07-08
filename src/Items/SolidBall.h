#ifndef SOLIDBALL_H
#define SOLIDBALL_H

#include "Weapon.h"

class SolidBall : public Weapon
{
public:
    explicit SolidBall(QGraphicsItem* parent);
    void attack(Character* user) override;

private:
    int throwCount = 3; // 投掷次数
};

#endif // SOLIDBALL_H
