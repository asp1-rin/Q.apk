cmake_minimum_required(VERSION 3.10.2)
project("Q-lib")
# 하위 폴더 연결
add_subdirectory(KittyMemory)

# 메인 라이브러리 빌드
add_library(Q-lib SHARED native-lib.cpp)

# 헤더 경로 및 라이브러리 연결
target_include_directories(Q-lib PRIVATE KittyMemory)
target_link_libraries(Q-lib KittyMemory log)
