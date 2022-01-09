cmake_minimum_required(VERSION 3.10.2)
project(DoodleJump)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5
        COMPONENTS
        system window graphics audio REQUIRED)

add_executable(DoodleJump
        src/main.cpp

        src/Utility/Stopwatch.cpp
        src/Utility/Stopwatch.h
        src/Utility/Random.cpp
        src/Utility/Random.h

        src/Game.cpp
        src/Game.h

        src/Game/World/World.cpp
        src/Game/World/World.h
        src/Game/World/Camera.cpp
        src/Game/World/Camera.h

        src/Game/GameObject/GameObject.cpp
        src/Game/GameObject/GameObject.h

        src/Game/GameObject/Collision/CollisionObject.cpp
        src/Game/GameObject/Collision/CollisionObject.h

        src/Game/GameObject/Entity/Entity.cpp
        src/Game/GameObject/Entity/Entity.h
        src/Game/GameObject/Entity/Player/Player.cpp
        src/Game/GameObject/Entity/Player/Player.h
        src/Game/GameObject/Entity/Platform/Platform.cpp
        src/Game/GameObject/Entity/Platform/Platform.h
        src/Game/GameObject/Entity/Platform/KinematicPlatform.cpp
        src/Game/GameObject/Entity/Platform/KinematicPlatform.h
        src/Game/GameObject/Entity/Platform/StaticPlatform.cpp
        src/Game/GameObject/Entity/Platform/StaticPlatform.h
        src/Game/GameObject/Entity/Bonus/Bonus.cpp
        src/Game/GameObject/Entity/Bonus/Bonus.h
        src/Game/GameObject/Entity/Bonus/Jetpack.cpp
        src/Game/GameObject/Entity/Bonus/Jetpack.h
        src/Game/GameObject/Entity/Bonus/Spring.cpp
        src/Game/GameObject/Entity/Bonus/Spring.h
        src/Game/GameObject/Entity/BGTile/BGTile.cpp
        src/Game/GameObject/Entity/BGTile/BGTile.h

        src/View/EntityView/EntityView.cpp
        src/View/EntityView/EntityView.h
        src/View/EntityView/PlayerView/PlayerView.cpp
        src/View/EntityView/PlayerView/PlayerView.h

        src/View/resources.h
        src/View/EntityView/DerivedEntityViews.h
        src/View/AbstractEntityFactory/AbstractEntityFactory.cpp
        src/View/AbstractEntityFactory/AbstractEntityFactory.h
        src/View/AbstractEntityFactory/SFMLEntityFactory/SFMLEntityFactory.cpp
        src/View/AbstractEntityFactory/SFMLEntityFactory/SFMLEntityFactory.h

        src/View/ResourceManager/ResourceManager.h
        src/View/Window/WindowManager.h
        src/View/Window/SFMLWindowManager.cpp
        src/View/Window/SFMLWindowManager.h

        src/Utility/Utility.cpp
        src/Utility/Utility.h)

target_link_libraries(DoodleJump sfml-system sfml-window sfml-graphics sfml-audio)

