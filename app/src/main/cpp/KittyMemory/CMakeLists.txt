cmake_minimum_required(VERSION 3.10.2)
project(KittyMemory)
# 파일이 없어도 빌드 오류 안 나게 빈 파일이라도 연결
add_library(KittyMemory STATIC KittyMemory.cpp)
target_include_directories(KittyMemory PUBLIC .)