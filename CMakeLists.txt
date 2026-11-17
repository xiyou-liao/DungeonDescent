cmake_minimum_required(VERSION 4.0)
project(finalProject)

set(CMAKE_CXX_STANDARD 23)

add_executable(finalProject
    main.cpp
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