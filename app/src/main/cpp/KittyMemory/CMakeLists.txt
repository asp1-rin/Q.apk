# CMake 최소 버전 설정
cmake_minimum_required(VERSION 3.10.2)

# 1. KittyMemory 프로젝트 이름 정의
project(KittyMemory)

# 2. 컴파일할 소스 파일들 등록
# KittyScanner.cpp는 구현이 복잡하므로 우선 기본적인 기능을 수행하는 파일들 위주로 등록합니다.
set(KITTY_SOURCES
    KittyMemory.cpp
    MemoryPatch.cpp
    # KittyScanner.cpp (패턴 스캔 기능이 필요할 때 추가)
)

# 3. 정적 라이브러리(Static Library) 생성
# SHARED 대신 STATIC을 사용하여 메인 바이너리에 포함시킵니다.
add_library(KittyMemory STATIC ${KITTY_SOURCES})

# 4. 헤더 파일 경로 설정
# 이 라이브러리를 사용하는 다른 파일들이 헤더를 찾을 수 있게 경로를 공개합니다.
target_include_directories(KittyMemory PUBLIC .)

# 5. 시스템 라이브러리 연결
# 안드로이드 로그와 동적 링크 라이브러리(dl)를 연결합니다.
target_link_libraries(KittyMemory android dl)
