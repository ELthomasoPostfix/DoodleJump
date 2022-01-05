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
        src/Utility/Camera.cpp
        src/Utility/Camera.h
        src/Utility/Random.cpp
        src/Utility/Random.h

        src/Game.cpp
        src/Game.h
        src/World.cpp
        src/World.h
        src/PhysicsEngine.cpp
        src/PhysicsEngine.h

        src/GameObject.cpp
        src/GameObject.h

        src/Collision/CollisionObject.cpp
        src/Collision/CollisionObject.h
            src/Collision/PhysicsBody/PhysicsBody.cpp
            src/Collision/PhysicsBody/PhysicsBody.h
                src/Collision/PhysicsBody/KinematicBody.cpp
                src/Collision/PhysicsBody/KinematicBody.h
                src/Collision/PhysicsBody/RigidBody.cpp
                src/Collision/PhysicsBody/RigidBody.h
                src/Collision/PhysicsBody/StaticBody.cpp
                src/Collision/PhysicsBody/StaticBody.h

        src/Entity/Entity.cpp
        src/Entity/Entity.h
            src/Entity/Player.cpp
            src/Entity/Player.h

        src/Utility/Utility.cpp
        src/Utility/Utility.h)

target_link_libraries(DoodleJump sfml-system sfml-window sfml-graphics sfml-audio)

