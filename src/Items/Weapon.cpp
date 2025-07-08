#include "Weapon.h"
#include "../Items/Characters/Character.h"
#include <QPainter>

Weapon::Weapon(QGraphicsItem* parent, const QString& pixmapPath, WeaponType type)
    : Equipment(parent, pixmapPath), type(type)
{
    if (!pixmapPath.isEmpty())
    {
        weaponPixmap.load(pixmapPath);
    }

    // 设置武器是否可见
    setVisible(type != FIST); // 拳头默认不显示
}

void Weapon::setFacingRight(bool facingRight)
{
    this->facingRight = facingRight;
}

QRectF Weapon::boundingRect() const
{
    // 使用图片原始尺寸作为边界框
    if (weaponPixmap.isNull()) {
        return QRectF(0, 0, 64, 64); // 默认大小
    }
    return QRectF(0, 0, weaponPixmap.width(), weaponPixmap.height());
}

void Weapon::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (!weaponPixmap.isNull())
    {
        if (facingRight)
        {
            painter->drawPixmap(0, 0, weaponPixmap);
        }
        else
        {
            painter->save();
            painter->translate(weaponPixmap.width(), 0);
            painter->scale(-1, 1);
            painter->drawPixmap(0, 0, weaponPixmap);
            painter->restore();
        }
    }
}

void Weapon::attack(Character* user)
{
    if (!active)
    {
        active = true;

        // 设置朝向
        facingRight = (user->transform().m11() > 0);

        // 只有拳头需要显示出来
        if (type == FIST)
        {
            setVisible(true);
        }

        // 已移除 0.5秒后隐藏武器的逻辑
        // 永久显示非拳头武器
    }
}

EquipmentCard* Weapon::createCard() const
{
    return new EquipmentCard(m_pixmapPath);
}
