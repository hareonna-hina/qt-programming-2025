//
// Created by gerw on 8/21/24.
//

#include "Map.h"

Map::Map(QGraphicsItem *parent, const QString &pixmapPath) : Item(parent, pixmapPath) {}


void Map::scaleToFitScene(QGraphicsScene *scene) {
    if (!scene || !pixmapItem) return;

    // 场景尺寸（1280x720）
    QRectF sceneRect = scene->sceneRect();
    // 图片原始尺寸
    QSize imgSize = pixmapItem->pixmap().size();

    qreal scaleX = sceneRect.width() / (qreal)imgSize.width();
    qreal scaleY = sceneRect.height() / (qreal)imgSize.height();
    qreal scaleFactor = qMin(scaleX, scaleY);

    // 应用缩放 + 居中
    setTransform(QTransform::fromScale(scaleFactor, scaleFactor), true);
    setPos(
        (sceneRect.width() - imgSize.width()*scaleFactor)/2,
        (sceneRect.height() - imgSize.height()*scaleFactor)/2
        );
}

QPointF Map::getSpawnPos() {
    auto boundingRect = sceneBoundingRect();
    auto midX = (boundingRect.left() + boundingRect.right()) * 0.5;
    return {midX, getFloorHeight()};
}

qreal Map::getFloorHeight() {
    auto sceneRect = sceneBoundingRect();
    return sceneRect.top() + (sceneRect.top() - sceneRect.bottom()) * 0.5;
}
