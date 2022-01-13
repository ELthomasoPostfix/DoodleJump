cmake_minimum_required(VERSION 3.10.2)
project(DoodleJump)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5
        COMPONENTS
        system window graphics audio REQUIRED)

add_library(DoodleLogic
        src/Utility/Utility.cpp
        src/Utility/Utility.h
        src/Utility/Stopwatch.cpp
        src/Utility/Stopwatch.h
        src/Utility/Random.cpp
        src/Utility/Random.h

        src/Game/AbstractEntityFactory/AbstractEntityFactory.cpp
        src/Game/AbstractEntityFactory/AbstractEntityFactory.h

        src/Event.h

        src/Game/World/World.cpp
        src/Game/World/World.h
        src/Game/World/CollisionInfo.h
        src/Game/World/Camera.cpp
        src/Game/World/Camera.h
        src/Game/World/Scoreboard.cpp
        src/Game/World/Scoreboard.h
        src/Game/World/Spawner.cpp
        src/Game/World/Spawner.h

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
        src/Game/GameObject/Entity/Platform/StaticPlatform.cpp
        src/Game/GameObject/Entity/Platform/StaticPlatform.h
        src/Game/GameObject/Entity/Platform/TemporaryPlatform.cpp
        src/Game/GameObject/Entity/Platform/TemporaryPlatform.h
        src/Game/GameObject/Entity/Platform/HorizontalPlatform.cpp
        src/Game/GameObject/Entity/Platform/HorizontalPlatform.h
        src/Game/GameObject/Entity/Platform/VerticalPlatform.cpp
        src/Game/GameObject/Entity/Platform/VerticalPlatform.h
        src/Game/GameObject/Entity/Bonus/Bonus.cpp
        src/Game/GameObject/Entity/Bonus/Bonus.h
        src/Game/GameObject/Entity/Bonus/Jetpack.cpp
        src/Game/GameObject/Entity/Bonus/Jetpack.h
        src/Game/GameObject/Entity/Bonus/Spring.cpp
        src/Game/GameObject/Entity/Bonus/Spring.h
        src/Game/GameObject/Entity/BGTile/BGTile.cpp
        src/Game/GameObject/Entity/BGTile/BGTile.h)

add_library(DoodleView
        src/View/ResourceManager/ResourceManager.h
        src/View/Window/WindowManager.h

        src/View/resources.h
        src/View/EntityView/EntityView.cpp
        src/View/EntityView/EntityView.h
        src/View/EntityView/TemplateView.cpp
        src/View/EntityView/TemplateView.h)

add_executable(DoodleJump
        src/main.cpp

        src/Game.cpp
        src/Game.h

        src/View/ConcreteEntityFactory/SFMLEntityFactory.cpp
        src/View/ConcreteEntityFactory/SFMLEntityFactory.h

        src/View/Window/SFMLWindowManager.cpp
        src/View/Window/SFMLWindowManager.h)

target_link_libraries(DoodleJump DoodleView DoodleLogic sfml-system sfml-window sfml-graphics sfml-audio)

