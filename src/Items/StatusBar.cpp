#include "StatusBar.h"
#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>

StatusBar::StatusBar(PlayerType playerType,
                     const QString& backgroundImagePath,
                     QGraphicsScene* scene)
    :QGraphicsItem(nullptr),m_playerType(playerType)
{
    if(!backgroundImagePath.isEmpty())
    {
        m_backgroundImage=QPixmap(backgroundImagePath);
        if(!m_backgroundImage.isNull())
        {
            m_width=m_backgroundImage.width();
            m_height=m_backgroundImage.height();
        }
    }
    setFlag(QGraphicsItem::ItemClipsChildrenToShape);
    if(scene)
    {
        scene->addItem(this);
    }

    // 加载心形图标
    fullHeartIcon = new QGraphicsPixmapItem(QPixmap(":/Items/Armors/FlamebreakerArmor/full_heart.png"), this);
    halfHeartIcon = new QGraphicsPixmapItem(QPixmap(":/Items/Armors/FlamebreakerArmor/half_heart.png"), this);
    emptyHeartIcon = new QGraphicsPixmapItem(QPixmap(":/Items/Armors/FlamebreakerArmor/empty_heart.png"), this);

    fullHeartIcon->setVisible(false);
    halfHeartIcon->setVisible(false);
    emptyHeartIcon->setVisible(false);

    // 创建初始心形显示
    createHeartItems();
}

void StatusBar::createHeartItems()
{
    // 清除现有心形
    for (auto heart : hearts)
    {
        if (scene())
        {
            scene()->removeItem(heart);
        }
        delete heart;
    }
    hearts.clear();

    // 创建5个心形占位符
    for (int i = 0; i < maxHearts(); i++)
    {
        auto heart = new QGraphicsPixmapItem(emptyHeartIcon->pixmap(), this);
        hearts.append(heart);
    }

    // 更新布局
    updateLayout();
}

void StatusBar::updateHearts(int health)
{
    // 每颗心20点生命值，每个半心10点
    int totalHearts=maxHearts();
    int fullHearts = health / 20;
    int halfHeart = (health % 20) >= 10 ? 1 : 0;

    fullHearts=qBound(0,fullHearts,totalHearts);
    halfHeart=qBound(0,halfHeart,1);

    for (int i = 0; i < totalHearts; i++) {
        if (i < fullHearts)
        {
            hearts[i]->setVisible(false);
            hearts[i]->setPixmap(fullHeartIcon->pixmap());
            hearts[i]->setVisible(true);
        }
        else if (i == fullHearts && halfHeart)
        {
            hearts[i]->setVisible(false);
            hearts[i]->setPixmap(halfHeartIcon->pixmap());
            hearts[i]->setVisible(true);
        }
        else
        {
            hearts[i]->setVisible(false);
            hearts[i]->setPixmap(emptyHeartIcon->pixmap());
            hearts[i]->setVisible(true);
        }
    }

    updateLayout();
}

void StatusBar::setGeometry(qreal x,qreal y,qreal width,qreal height)
{
    setPos(x,y);
    m_width=width;
    m_height=height;
    updateLayout();
}

QRectF StatusBar::boundingRect() const
{
    return QRectF(0, 0, m_width, m_height);
}

void StatusBar::paint(QPainter* painter,
                      const QStyleOptionGraphicsItem* option,
                      QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(!m_backgroundImage.isNull())
    {
        painter->drawPixmap(0,0,m_width,m_height,m_backgroundImage);
    }
}

void StatusBar::addEquipmentCard(EquipmentCard* card)
{
    if(!card) return;

    card->setParentItem(this);
    card->setScale(0.7);
    m_cards.append(card);

    updateLayout();
    update();
}

void StatusBar::removeEquipmentCard(EquipmentCard* card)
{
    if(!card) return;
    if(m_cards.removeOne(card))
    {
        if(scene())
        {
            scene()->removeItem(card);
        }
        delete card;
        updateLayout();
        update();
    }
}

void StatusBar::clearEquipmentCards()
{
    for(EquipmentCard* card:m_cards)
    {
        if(scene())
        {
            scene()->removeItem(card);
        }
        delete card;
    }
    m_cards.clear();
    update();
}

void StatusBar::updateLayout()
{
    // 心形图标布局
    const qreal heartSize = 32;
    const qreal heartSpacing = 15;
    qreal heartsWidth = maxHearts() * (heartSize + heartSpacing) - heartSpacing;

    // 计算起始位置（居中）
    qreal heartsX = (m_width - heartsWidth-60) / 2;
    qreal heartsY = 20;

    for (int i = 0; i < hearts.size(); i++)
    {
        hearts[i]->setPos(heartsX + i * (heartSize + heartSpacing), heartsY);
        hearts[i]->setScale(1);
    }


    //计算卡片区域大小
    const qreal cardAreaHeight=m_height*0.7;
    const qreal cardAreaWidth=m_width-2*m_padding;

    //计算卡片尺寸
    const qreal cardHeight =cardAreaHeight-10;
    const qreal cardWidth=cardHeight*0.5;

    //计算最多可以显示的卡牌数
    const int maxVisibleCards =qMax(1,static_cast<int>((cardAreaWidth - cardWidth) / (cardWidth * 0.2 + 5))+1);

    //确定卡牌位置，放在状态栏底部
    const qreal yPos=m_height -cardAreaHeight;

    //水平排列所有可见的卡片
    const int cardCount=qMin(maxVisibleCards,m_cards.size());
    const qreal spacing=(cardAreaWidth - cardCount * cardWidth) / (cardCount + 1);

    //布局卡片
    for(int i=0;i<cardCount;++i)
    {
        qreal xPos=m_padding+spacing*(i+1)+cardWidth*i;
        m_cards[i]->setPos(xPos,yPos);
    }

    //处理超出窗口大小的卡片
    if(m_cards.size()>maxVisibleCards)
    {
        for(int i=maxVisibleCards;i<m_cards.size();++i)
        {
            m_cards[i]->setVisible(false);
        }
    }
    if(m_cards.empty()) return;
}




















