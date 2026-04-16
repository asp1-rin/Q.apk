cmake_minimum_required(VERSION 3.22.1)

project(KittyMemory)

# .cpp 파일만 적습니다. .hpp는 적지 않아도 자동으로 참조됩니다.
add_library(KittyMemory STATIC
            KittyMemory.cpp
            KittyScanner.cpp
)

target_include_directories(KittyMemory PUBLIC .)
