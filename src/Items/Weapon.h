#ifndef WEAPON_H
#define WEAPON_H

#include "Equipment.h"
#include <QTimer>

enum WeaponType
{
    FIST,
    KNIFE,
    SOLID_BALL,
    RIFLE,
    SNIPER
};

class Character;

class Weapon:public Equipment
{
public:
    explicit Weapon(QGraphicsItem* parent,const QString& pixmapPath,WeaponType type);

    virtual void attack(Character* user);
    WeaponType getType() const {return type;}
    bool isActive() const {return active;}

    void setFacingRight(bool facingRight);

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,QWidget* widget) override;
    int getDamage(){return damage;}
    virtual EquipmentCard* createCard() const override;
protected:
    WeaponType type;
    bool active=false;
    bool facingRight=true;
    QTimer* attackTimer=nullptr;
    QPixmap weaponPixmap;
    int damage;
};



#endif // WEAPON_H
