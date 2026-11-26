cmake_minimum_required(VERSION 4.0)
project(finalProject)

set(CMAKE_CXX_STANDARD 23)

add_executable(finalProject
    main.cpp
        game/game.h
        game/Game.cpp
        game/Scene.h
        game/Scene.cpp
        entities/Entity.h
        entities/Entity.cpp
        game/Map.h
        entities/Player.h
        entities/Player.cpp
        items/Weapon.h
        items/Weapon.cpp
        items/item.h
        items/Item.cpp
        entities/CodingGoblin.h
        entities/CodingGoblin.cpp
        entities/Enemy.h
        entities/Enemy.cpp
)

target_include_directories(finalProject PRIVATE
        C:/raylib/include
)

target_link_directories(finalProject PRIVATE
        C:/raylib/lib
)

target_link_libraries(finalProject PRIVATE
        raylib
        opengl32
        gdi32
        winmm
)