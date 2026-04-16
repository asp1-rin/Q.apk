cmake_minimum_required(VERSION 3.10.2)
project(MilkChocoHack)

add_subdirectory(KittyMemory)

include_directories(include modules KittyMemory)

add_library(BypassModule SHARED
            main.cpp
            modules/Bypass.cpp
            modules/Weapon.cpp
            modules/Aimbot.cpp
            modules/Esp.cpp)

target_link_libraries(BypassModule KittyMemory android log dl)
