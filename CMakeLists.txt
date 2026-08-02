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

add_executable(lowrez Main.cpp)

target_sources(lowrez PRIVATE
    Main.cpp
    src/Game.cpp
    src/Object.cpp
    src/NullObject.cpp
    src/Tilemap.cpp
    
    src/Game.hpp
    src/Object.hpp
    src/NullObject.hpp
    src/Tilemap.hpp
)

target_include_directories(lowrez PRIVATE src)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(lowrez PRIVATE 
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
endif()

add_custom_command(
    TARGET lowrez 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:lowrez>/assets"
)
