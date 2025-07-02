#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Item.h"
#include "EquipmentCard.h"

class Equipment : public Item {
public:
    explicit Equipment(QGraphicsItem* parent, const QString& pixmapPath)
        : Item(parent, pixmapPath) {}

    virtual ~Equipment() = default;

    virtual EquipmentCard* createCard() const = 0;
};

#endif // EQUIPMENT_H
