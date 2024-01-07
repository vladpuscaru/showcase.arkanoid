cmake_minimum_required(VERSION 3.14)
project(arkanoid)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES src/main.cpp
        src/engine/Action/Action.h
        src/engine/Action/Action.cpp
        src/engine/Animation/Animation.h
        src/engine/Animation/Animation.cpp
        src/engine/Assets/Assets.h
        src/engine/Assets/Assets.cpp
        src/engine/Components/Components.h
        src/engine/Entities/Entity/Entity.h
        src/engine/Entities/Entity/Entity.cpp
        src/engine/Entities/EntityManager/EntityManager.h
        src/engine/Entities/EntityManager/EntityManager.cpp
        src/engine/Physics/Physics.cpp
        src/engine/GameEngine/GameEngine.h
        src/engine/util/util.h
        src/engine/GameEngine/GameEngine.cpp
        src/engine/Scene/Scene.cpp
        src/scenes/ScenePlay/ScenePlay.h
        src/scenes/ScenePlay/ScenePlay.cpp
        src/scenes/constants.h
)
add_executable(arkanoid ${SOURCE_FILES})

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(arkanoid sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

file(COPY assets DESTINATION .)