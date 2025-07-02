#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QGraphicsItem>
#include <QList>
#include <QPixmap>
#include "EquipmentCard.h"

class StatusBar : public QGraphicsItem{
public:
    enum PlayerType {PLAYER_1,PLAYER_2};

    explicit StatusBar(PlayerType playerType,
                       const QString& backgroundImagePath,
                       QGraphicsScene* parent=nullptr);

    void setGeometry(qreal x,qreal y, qreal width, qreal height);

    void addEquipmentCard(EquipmentCard * card);
    void removeEquipmentCard(EquipmentCard *card);
    void clearEquipmentCards();

    QRectF boundingRect()const override;
    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget=nullptr) override;

    PlayerType playerType() const {return m_playerType;}

private:
    void updateLayout();
    PlayerType m_playerType;
    QPixmap m_backgroundImage;
    QList<EquipmentCard*> m_cards;

    qreal m_width =200;
    qreal m_height=100;
    qreal m_padding=10;
};





#endif // STATUSBAR_H
