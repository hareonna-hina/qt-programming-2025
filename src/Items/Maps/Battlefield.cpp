//
// Created by gerw on 8/21/24.
//

#include "Battlefield.h"

Battlefield::Battlefield(QGraphicsItem *parent) : Map(parent, ":/Items/Maps/Battlefield/map.png") {}

qreal Battlefield::getFloorHeight() {
    auto sceneRect = sceneBoundingRect();
    return (sceneRect.top() + sceneRect.bottom()) * 0.7;
}

qreal Battlefield::getFloorHeightAt(qreal x) const
{
    auto sceneRect = sceneBoundingRect();
    return (sceneRect.top() + sceneRect.bottom()) * 0.7;
}

qreal Battlefield::getCeilingHeight() const
{
    auto sceneRect=sceneBoundingRect();
    return sceneRect.top()+50;
}

//检查矩形底部是否在地面高度之上
bool Battlefield::isSolidAt(const QRectF& rect) const
{
    qreal groundY=getFloorHeightAt(rect.center().x());
    return rect.bottom()>=groundY;
}
