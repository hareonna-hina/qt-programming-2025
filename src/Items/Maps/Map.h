//
// Created by gerw on 8/21/24.
//

#ifndef QT_PROGRAMMING_2024_MAP_H
#define QT_PROGRAMMING_2024_MAP_H

#include <QGraphicsScene>
#include <QPointF>
#include "../Item.h"

class Character;

class Map : public Item {
public:
    explicit Map(QGraphicsItem *parent = nullptr, const QString &pixmapPath = "");

    void scaleToFitScene(QGraphicsScene *scene);

    virtual qreal getFloorHeight(); // Need to rewrite to support multiple platforms

    virtual QPointF getSpawnPos();

    virtual qreal getFloorHeightAt(qreal x) const=0;

    virtual bool isSolidAt(const QRectF& rect) const=0;

    virtual qreal getCeilingHeight() const=0;
};


#endif //QT_PROGRAMMING_2024_MAP_H
