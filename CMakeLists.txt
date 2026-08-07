cmake_minimum_required(VERSION 3.11.0)
project(LOWREZJAM2026)

message(STATUS "Build platform is ${CMAKE_SYSTEM_NAME}")

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    include_directories(${CMAKE_SOURCE_DIR}/libs/linux/raylib/include)
    link_directories(${CMAKE_SOURCE_DIR}/libs/linux/raylib/lib)
endif()

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    include_directories(${CMAKE_SOURCE_DIR}/libs/windows/raylib/include)
    link_directories(${CMAKE_SOURCE_DIR}/libs/windows/raylib/lib)
endif()

list(APPEND src_files
    src/Game.cpp
    src/Object.cpp
    src/NullObject.cpp
    src/Tilemap.cpp
    src/Animation.cpp
    src/Entity.cpp
    src/Helper.cpp
    src/Door.cpp
    src/Character.cpp
    src/Player.cpp
    src/monsters/Crab.cpp
    src/monsters/Seagull.cpp
    src/monsters/Bullet.cpp
    src/monsters/Pirate.cpp
    src/Weapon.cpp
    src/weapons/RollingPin.cpp
    
    Load.hpp
    src/Game.hpp
    src/Object.hpp
    src/NullObject.hpp
    src/Tilemap.hpp
    src/Animation.hpp
    src/Entity.hpp
    src/Helper.hpp
    src/Door.hpp
    src/Character.hpp
    src/Player.hpp
    src/monsters/Crab.hpp
    src/monsters/Seagull.hpp
    src/monsters/Bullet.hpp
    src/monsters/Pirate.hpp
    src/Weapon.hpp
    src/weapons/RollingPin.hpp
)

add_executable(lowrez Main.cpp)

add_executable(lowrez-editor Editor.cpp)

target_sources(lowrez PRIVATE ${src_files})

target_sources(lowrez-editor PRIVATE ${src_files})

target_include_directories(lowrez PRIVATE src)

target_include_directories(lowrez-editor PRIVATE src)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(lowrez PRIVATE 
            raylib
            X11
            )
    target_link_libraries(lowrez-editor PRIVATE 
            raylib
            X11
            )
endif()


if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(lowrez PRIVATE 
            raylib
            opengl32
            winmm
            gdi32
            )
    target_link_libraries(lowrez-editor PRIVATE 
            raylib
            opengl32
            winmm
            gdi32
            )
endif()

add_custom_command(
    TARGET lowrez 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:lowrez>/assets"
)
