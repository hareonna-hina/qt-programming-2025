//
// Created by gerw on 8/20/24.
//

#include "HeadEquipment.h"

HeadEquipment::HeadEquipment(QGraphicsItem *parent, const QString &pixmapPath) : Equipment(parent, pixmapPath),pixmapPath_1(pixmapPath) {}

EquipmentCard* HeadEquipment::createCard() const{
    return new EquipmentCard(pixmapPath_1);
}
