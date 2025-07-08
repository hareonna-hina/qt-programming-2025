#include "Projectile.h"
#include <QPainter>
#include <QTimer>
#include <QGraphicsScene>

Projectile::Projectile(QPointF startPos, bool facingRight, qreal vx, qreal vy)
    : facingRight(facingRight), vx(vx), vy(vy)
{
    if (!facingRight)
    {
        vx = -vx; // 朝左时反向
    }

    setPos(startPos);

    // 设置投掷物大小
    setRect(QRectF(0, 0, 15, 15)); // 圆形投掷物

    // 设置移动定时器
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Projectile::move);
    timer->start(50); // 每50ms移动一次
}

QRectF Projectile::boundingRect() const
{
    return QRectF(0, 0, 15, 15);
}

void Projectile::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::gray);
    painter->drawEllipse(0, 0, 15, 15);
}

void Projectile::move()
{
    // 应用加速度
    vx += ax;
    vy += ay;

    // 更新位置
    setPos(x() + vx, y() + vy);

    // 检查是否超出场景边界或落地
    if (x() < 0 || x() > 1280 || y() > 720)
    {
        scene()->removeItem(this);
        delete this;
    }
}
