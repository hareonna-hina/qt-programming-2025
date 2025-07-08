#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsItem>
#include <QObject>

class Bullet : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Bullet(QPointF startPos, bool facingRight, qreal speed, int damage = 10);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    int getDamage(){return damage;}

    void setRect(const QRectF &rect){m_rect=rect;}

public slots:
    void move();

private:
    bool facingRight;
    qreal speed;
    int damage;
    QRectF m_rect;
};
#endif // BULLET_H
