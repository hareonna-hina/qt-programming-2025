//
// Created by gerw on 8/20/24.
//

#include "LegEquipment.h"

LegEquipment::LegEquipment(QGraphicsItem *parent, const QString &pixmapPath) : Equipment(parent, pixmapPath),pixmapPath_1(pixmapPath) {}

EquipmentCard* LegEquipment::createCard() const{
    return new EquipmentCard(pixmapPath_1);
}

