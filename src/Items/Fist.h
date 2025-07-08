#ifndef FIST_H
#define FIST_H

#include "Weapon.h"

class Fist:public Weapon
{
public:
    explicit Fist(QGraphicsItem* parent);
    void attack(Character* user) override;
};


#endif // FIST_H
