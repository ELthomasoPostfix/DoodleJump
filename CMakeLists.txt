cmake_minimum_required(VERSION 3.10.2)
project(DoodleJump)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5
        COMPONENTS
        system window graphics audio REQUIRED)

add_executable(DoodleJump main.cpp)
target_link_libraries(DoodleJump sfml-system sfml-window sfml-graphics sfml-audio)

