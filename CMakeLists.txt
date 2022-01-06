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

        src/Game/Game.cpp
        src/Game/Game.h
        src/Game/World/World.cpp
        src/Game/World/World.h
        src/Game/World/PhysicsEngine.cpp
        src/Game/World/PhysicsEngine.h
        src/Game/World/Camera.cpp
        src/Game/World/Camera.h

        src/Game/GameObject/GameObject.cpp
        src/Game/GameObject/GameObject.h

        src/Game/GameObject/Collision/CollisionObject.cpp
        src/Game/GameObject/Collision/CollisionObject.h
        src/Game/GameObject/Collision/PhysicsBody/PhysicsBody.cpp
        src/Game/GameObject/Collision/PhysicsBody/PhysicsBody.h
        src/Game/GameObject/Collision/PhysicsBody/KinematicBody.cpp
        src/Game/GameObject/Collision/PhysicsBody/KinematicBody.h
        src/Game/GameObject/Collision/PhysicsBody/RigidBody.cpp
        src/Game/GameObject/Collision/PhysicsBody/RigidBody.h
        src/Game/GameObject/Collision/PhysicsBody/StaticBody.cpp
        src/Game/GameObject/Collision/PhysicsBody/StaticBody.h

        src/Game/GameObject/Entity/Entity.cpp
        src/Game/GameObject/Entity/Entity.h
        src/Game/GameObject/Entity/Player.cpp
        src/Game/GameObject/Entity/Player.h

        src/Game/GameObject/View/View.cpp
        src/Game/GameObject/View/View.h

        src/Utility/Utility.cpp
        src/Utility/Utility.h)

target_link_libraries(DoodleJump sfml-system sfml-window sfml-graphics sfml-audio)

