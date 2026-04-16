# CMake 최소 버전 요구사항
cmake_minimum_required(VERSION 3.10.2)

# 프로젝트 이름 설정
project(MilkChocoHack)

# 1. KittyMemory 서브 프로젝트 포함
# KittyMemory 폴더 안의 CMakeLists.txt를 실행하여 KittyMemory 정적 라이브러리를 생성합니다.
add_subdirectory(KittyMemory)

# 2. 헤더 파일 검색 경로 설정
# 소스 코드에서 #include "KittyInclude.hpp" 등을 찾을 수 있게 폴더 위치를 알려줍니다.
include_directories(
    include          # offsets.h 가 있는 곳
    modules          # Bypass.cpp, Weapon.cpp 등이 있는 곳
    KittyMemory      # KittyMemory 헤더들이 있는 곳
)

# 3. 최종 공유 라이브러리(.so) 빌드 설정
# 이제 모든 모듈(Bypass, Weapon, Aimbot, Esp)을 합쳐서 하나의 파일로 만듭니다.
add_library(BypassModule SHARED
            main.cpp
            modules/Bypass.cpp
            modules/Weapon.cpp
            modules/Aimbot.cpp
            modules/Esp.cpp
)

# 4. 라이브러리 링크 (연결 작업)
# BypassModule이 작동하는 데 필요한 외부 라이브러리들을 엮어줍니다.
target_link_libraries(BypassModule
                      KittyMemory   # 위에서 add_subdirectory로 만든 라이브러리
                      android       # 안드로이드 네이티브 API
                      log           # 로그캣 출력용 (__android_log_print)
                      dl            # 동적 링커 (dlsym, dlopen 사용 필수)
)
