//
// Created by gerw on 8/21/24.
//

#ifndef QT_PROGRAMMING_2024_BATTLEFIELD_H
#define QT_PROGRAMMING_2024_BATTLEFIELD_H


#include "Map.h"

class Battlefield: public Map {
public:
    explicit Battlefield(QGraphicsItem *parent= nullptr);

    qreal getFloorHeight() override;

    virtual bool isSolidAt(const QRectF& rect) const override;

    virtual qreal getFloorHeightAt(qreal x) const override;

    virtual qreal getCeilingHeight() const override;
};


#endif //QT_PROGRAMMING_2024_BATTLEFIELD_H
