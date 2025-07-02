//
// Created by gerw on 8/20/24.
//

#ifndef QT_PROGRAMMING_2024_LEGEQUIPMENT_H
#define QT_PROGRAMMING_2024_LEGEQUIPMENT_H


#include "../Item.h"
#include "../Mountable.h"
#include "../Equipment.h"

class LegEquipment: public Equipment {
private:
    QString pixmapPath_1;
public:
    explicit LegEquipment(QGraphicsItem *parent, const QString &pixmapPath);

    EquipmentCard* createCard() const override;
};


#endif //QT_PROGRAMMING_2024_LEGEQUIPMENT_H
