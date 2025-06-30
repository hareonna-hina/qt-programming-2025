//
// Created by gerw on 8/21/24.
//

#include "Mountable.h"
#include "Characters/Character.h"
void Mountable::unmount() {
    mounted = false;
}

bool Mountable::isMounted() const {
    return mounted;
}

void Mountable::mountToParent(Character *character) {
    mounted = true;
}
