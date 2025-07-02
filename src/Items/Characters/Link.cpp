//
// Created by gerw on 8/20/24.
//

#include <memory>
#include "Link.h"
#include "../HeadEquipments/CapOfTheHero.h"
#include "../Armors/OldShirt.h"
#include "../LegEquipments/WellWornTrousers.h"

Link::Link(Character::CharacterType type, QGraphicsItem *parent)
    : Character(type, parent) {

    // 根据角色类型加载不同装备
    /*if (type == Character::TYPE_PLAYER1)
    {
        headEquipment = new CapOfTheHero(this);
        legEquipment = new WellWornTrousers(this);
        armor = new OldShirt(this);
        headEquipment->mountToParent(this);
        legEquipment->mountToParent(this);
        armor->mountToParent(this);
    }
    else {
        // 为玩家2创建不同装备（示例，具体使用其他装备类）
        headEquipment = new CapOfTheHero(this);
        legEquipment = new WellWornTrousers(this);
        armor = new OldShirt(this);
        headEquipment->mountToParent(this);
        legEquipment->mountToParent(this);
        armor->mountToParent(this);
    }
*/
    // headEquipment = new CapOfTheHero(this);
    // legEquipment = new WellWornTrousers(this);
    // armor = new OldShirt(this);
    // headEquipment->mountToParent(this);
    // legEquipment->mountToParent(this);
    // armor->mountToParent(this);

}
