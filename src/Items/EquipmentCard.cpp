#include "EquipmentCard.h"
#include <QPainter>

EquipmentCard ::EquipmentCard(const QString& iconPath, QGraphicsItem* parent)
    :QGraphicsItem(parent),icon(iconPath){
    setScale(0.5);
}

QRectF EquipmentCard::boundingRect() const{
    return QRectF(0,0,icon.width(),icon.height());
}

void EquipmentCard::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
    painter->drawPixmap(0,0,icon);
}
