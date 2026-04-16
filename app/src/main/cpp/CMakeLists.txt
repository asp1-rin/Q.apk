# CMake 최소 버전 요구사항
cmake_minimum_required(VERSION 3.10.2)

# 프로젝트 이름
project(MilkChocoHack)

# 1. 서브 디렉토리 포함 (KittyMemory 폴더의 CMakeLists.txt를 먼저 실행)
add_subdirectory(KittyMemory)

# 2. 헤더 파일 경로 설정 (include 폴더와 각 모듈 폴더를 참조하도록 설정)
include_directories(
    include
    modules
    KittyMemory
)

# 3. 메인 공유 라이브러리(.so) 생성
# 여기에 작성한 파일들이 합쳐져 'libBypassModule.so'가 됩니다.
add_library(BypassModule SHARED
            main.cpp
            modules/Bypass.cpp
            modules/Weapon.cpp
            # modules/Aimbot.cpp (에임봇 추가 시 주석 해제)
)

# 4. 라이브러리 간 연결 (Linker 설정)
# 우리 모듈이 KittyMemory와 안드로이드 시스템 로그 등을 사용하도록 연결합니다.
target_link_libraries(BypassModule
                      KittyMemory   # 서브 프로젝트에서 생성된 정적 라이브러리
                      android       # 안드로이드 시스템 라이브러리
                      log           # 로그 출력용 (__android_log_print)
                      dl            # 동적 로딩용 (dlopen, dlsym)
)
