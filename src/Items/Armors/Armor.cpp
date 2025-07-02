//
// Created by gerw on 8/20/24.
//

#include "Armor.h"

Armor::Armor(QGraphicsItem *parent, const QString &pixmapPath) : Equipment(parent, pixmapPath),pixmapPath_1(pixmapPath) {}

EquipmentCard* Armor::createCard() const{
    return new EquipmentCard(pixmapPath_1);
}
