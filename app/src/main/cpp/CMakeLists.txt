cmake_minimum_required(VERSION 3.22.1)
project(QModule)

add_subdirectory(KittyMemory)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/modules
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/KittyMemory
)

add_library(BypassModule SHARED
            main.cpp
            modules/Bypass.cpp
            modules/Weapon.cpp
            modules/Aimbot.cpp
            modules/Esp.cpp)

target_link_libraries(BypassModule KittyMemory android log dl)
