cmake_minimum_required(VERSION 3.28)
project(qt_programming_2024)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(qt_programming_2024 src/main.cpp
        src/MyGame.cpp
        src/MyGame.h
        src/Items/Item.cpp
        src/Items/Item.h
        src/Items/Characters/Character.cpp
        src/Items/Characters/Character.h
        src/Items/Characters/Link.cpp
        src/Items/Characters/Link.h
        src/Items/Armors/Armor.cpp
        src/Items/Armors/Armor.h
        src/Items/HeadEquipments/HeadEquipment.cpp
        src/Items/HeadEquipments/HeadEquipment.h
        src/Items/LegEquipments/LegEquipment.cpp
        src/Items/LegEquipments/LegEquipment.h
        src/Items/HeadEquipments/CapOfTheHero.cpp
        src/Items/HeadEquipments/CapOfTheHero.h
        src/Items/Armors/OldShirt.cpp
        src/Items/Armors/OldShirt.h
        src/Items/LegEquipments/WellWornTrousers.cpp
        src/Items/LegEquipments/WellWornTrousers.h
        src/Scenes/Scene.cpp
        src/Scenes/Scene.h
        src/Scenes/BattleScene.cpp
        src/Scenes/BattleScene.h
        assets/assets.qrc
        src/Items/Maps/Map.cpp
        src/Items/Maps/Map.h
        src/Items/Maps/Battlefield.cpp
        src/Items/Maps/Battlefield.h
        src/Items/Mountable.cpp
        src/Items/Mountable.h
        src/Items/Armors/FlamebreakerArmor.cpp
        src/Items/Armors/FlamebreakerArmor.h
        src/Items/EquipmentCard.h
        src/Items/EquipmentCard.cpp
        src/Items/Equipment.h
        src/Items/StatusBar.h
        src/Items/StatusBar.cpp
        src/Items/Weapon.h
        src/Items/Weapon.cpp
        src/Items/Fist.h
        src/Items/Fist.cpp
        src/Items/Knife.h
        src/Items/Knife.cpp
        src/Items/SolidBall.h
        src/Items/SolidBall.cpp
        src/Items/Rifle.h
        src/Items/Rifle.cpp
        src/Items/Sniper.h
        src/Items/Sniper.cpp
        src/Items/Bullet.h
        src/Items/Bullet.cpp
        src/Items/Projectile.h
        src/Items/Projectile.cpp
        src/Items/Equipment.cpp











)
target_link_libraries(qt_programming_2024
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

