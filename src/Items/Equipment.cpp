#include "Equipment.h"

EquipmentCard* Equipment::createCard() const
{
    return new EquipmentCard(m_pixmapPath);
}
