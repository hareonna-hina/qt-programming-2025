//
// Created by gerw on 8/20/24.
//

#ifndef QT_PROGRAMMING_2024_LINK_H
#define QT_PROGRAMMING_2024_LINK_H


#include "Character.h"

class Link : public Character {
public:
    // 添加角色类型参数
    explicit Link(Character::CharacterType type, QGraphicsItem *parent = nullptr);
};


#endif //QT_PROGRAMMING_2024_LINK_H
