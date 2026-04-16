cmake_minimum_required(VERSION 3.22.1)
project(QModule)

add_subdirectory(KittyMemory)

# 경로 설정 최적화 (src/main/cpp 중복 제거)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/modules
    ${CMAKE_CURRENT_SOURCE_DIR}/KittyMemory
)

add_library(BypassModule SHARED
            main.cpp
            modules/Bypass.cpp
            modules/Weapon.cpp
            modules/Aimbot.cpp
            modules/Esp.cpp)

target_link_libraries(BypassModule KittyMemory android log dl)
