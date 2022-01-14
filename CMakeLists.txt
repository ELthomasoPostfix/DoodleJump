cmake_minimum_required(VERSION 3.10.2)
project(DoodleJump)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5
        COMPONENTS
        system window graphics audio REQUIRED)

add_library(DoodleLogic STATIC
        src/Utility/Utility.cpp
        src/Utility/Utility.h
        src/Utility/Stopwatch.cpp
        src/Utility/Stopwatch.h
        src/Utility/Random.cpp
        src/Utility/Random.h

        src/Model/AbstractEntityFactory/AbstractEntityFactory.cpp
        src/Model/AbstractEntityFactory/AbstractEntityFactory.h

        src/Model/World/Event.h

        src/Model/World/World.cpp
        src/Model/World/World.h
        src/Model/World/CollisionInfo.h
        src/Model/World/Camera.cpp
        src/Model/World/Camera.h
        src/Model/World/Scoreboard.cpp
        src/Model/World/Scoreboard.h
        src/Model/World/Spawner.cpp
        src/Model/World/Spawner.h

        src/Model/GameObject/GameObject.cpp
        src/Model/GameObject/GameObject.h

        src/Model/GameObject/Collision/CollisionObject.cpp
        src/Model/GameObject/Collision/CollisionObject.h

        src/Model/GameObject/Entity/Entity.cpp
        src/Model/GameObject/Entity/Entity.h
        src/Model/GameObject/Entity/Player/Player.cpp
        src/Model/GameObject/Entity/Player/Player.h
        src/Model/GameObject/Entity/Platform/Platform.cpp
        src/Model/GameObject/Entity/Platform/Platform.h
        src/Model/GameObject/Entity/Platform/StaticPlatform.cpp
        src/Model/GameObject/Entity/Platform/StaticPlatform.h
        src/Model/GameObject/Entity/Platform/TemporaryPlatform.cpp
        src/Model/GameObject/Entity/Platform/TemporaryPlatform.h
        src/Model/GameObject/Entity/Platform/HorizontalPlatform.cpp
        src/Model/GameObject/Entity/Platform/HorizontalPlatform.h
        src/Model/GameObject/Entity/Platform/VerticalPlatform.cpp
        src/Model/GameObject/Entity/Platform/VerticalPlatform.h
        src/Model/GameObject/Entity/Bonus/Bonus.cpp
        src/Model/GameObject/Entity/Bonus/Bonus.h
        src/Model/GameObject/Entity/Bonus/Jetpack.cpp
        src/Model/GameObject/Entity/Bonus/Jetpack.h
        src/Model/GameObject/Entity/Bonus/Spring.cpp
        src/Model/GameObject/Entity/Bonus/Spring.h
        src/Model/GameObject/Entity/BGTile/BGTile.cpp
        src/Model/GameObject/Entity/BGTile/BGTile.h)

add_library(DoodleView STATIC
        src/View/ResourceManager/ResourceManager.h
        src/View/Window/WindowManager.h

        src/View/resources.h
        src/View/EntityView/EntityView.cpp
        src/View/EntityView/EntityView.h
        src/View/EntityView/TemplateView.cpp
        src/View/EntityView/TemplateView.h)

add_executable(DoodleJump
        src/Controller/main.cpp

        src/Controller/Game.cpp
        src/Controller/Game.h

        src/Controller/SFMLEntityFactory.cpp
        src/Controller/SFMLEntityFactory.h

        src/Controller/SFMLWindowManager.cpp
        src/Controller/SFMLWindowManager.h)

target_link_libraries(DoodleJump DoodleView DoodleLogic sfml-system sfml-window sfml-graphics sfml-audio)

