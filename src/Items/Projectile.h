#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QGraphicsItem>
#include <QObject>

class Projectile : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Projectile(QPointF startPos, bool facingRight, qreal vx, qreal vy);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    int getDamage(){return damage;}
    void setRect(const QRectF &rect){m_rect=rect;}

public slots:
    void move();

private:
    bool facingRight;
    qreal vx, vy; // 初始速度分量
    qreal ax = 0, ay = 0.5; // 加速度（重力）
    int damage=0;
    QRectF m_rect;
};

#endif // PROJECTILE_H

