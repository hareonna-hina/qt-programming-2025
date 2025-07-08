#ifndef KNIFE_H
#define KNIFE_H

#include "Weapon.h"

class Knife:public Weapon
{
public:
    explicit Knife(QGraphicsItem* parent);
    void attack(Character* user) override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};

#endif // KNIFE_H
