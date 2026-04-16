cmake_minimum_required(VERSION 3.10.2)

project(KittyMemory)

# 소스 파일 목록 정의 (파일 이름이 정확한지 확인하세요)
add_library(KittyMemory
    STATIC
    KittyMemory.cpp
    MemoryPatch.cpp
    MemoryBackup.cpp
    KittyUtils.cpp
)

# 헤더 파일 경로 포함
target_include_directories(KittyMemory PUBLIC .)
