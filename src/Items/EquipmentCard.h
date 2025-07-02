#ifndef EQUIPMENTCARD_H
#define EQUIPMENTCARD_H

#include <QGraphicsItem>

class EquipmentCard : public QGraphicsItem{
public:
    explicit EquipmentCard (const QString& iconPath, QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget=nullptr) override;

private:
    QPixmap icon;
};

#endif // EQUIPMENTCARD_H
