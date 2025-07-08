#include "Bullet.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

Bullet::Bullet(QPointF startPos, bool facingRight, qreal speed, int damage)
    : facingRight(facingRight), speed(speed), damage(damage)
{
    setPos(startPos);

    // 设置子弹大小
    setRect(QRectF(0, 0, 10, 5)); // 长条形子弹

    // 设置移动定时器
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bullet::move);
    timer->start(50); // 每50ms移动一次
}

QRectF Bullet::boundingRect() const
{
    return QRectF(0, 0, 10, 5);
}

void Bullet::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::red);
    painter->drawRect(0, 0, 10, 5);
}

void Bullet::move()
{
    // 根据方向移动
    if (facingRight)
    {
        setPos(x() + speed, y());
    }
    else
    {
        setPos(x() - speed, y());
    }

    // 检查是否超出场景边界
    if (x() < 0 || x() > 1280)
    {
        scene()->removeItem(this);
        delete this;
    }
}
