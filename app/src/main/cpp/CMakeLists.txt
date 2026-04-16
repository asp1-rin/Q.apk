cmake_minimum_required(VERSION 3.10.2)
project("admin-logic")

# 1. 안드로이드 로그 출력을 위한 라이브러리 설정
find_library(log-lib log)

# 2. KittyMemory 소스 파일 경로 설정
# 만약 폴더 구조가 KittyMemory/KittyMemory/ 폴더 안에 소스가 있다면 
# 아래 경로에 /KittyMemory를 한 번 더 추가해야 할 수도 있습니다.
set(KITTY_SRC
    KittyMemory/KittyMemory.cpp
    KittyMemory/MemoryPatch.cpp
    KittyMemory/MemoryUtils.cpp
    KittyMemory/MemoryBackup.cpp
)

# 3. 네이티브 라이브러리 빌드 정의
# native-lib.cpp와 키티메모리 소스들을 합쳐서 admin-logic.so를 만듭니다.
add_library(admin-logic SHARED 
    native-lib.cpp 
    ${KITTY_SRC}
)

# 4. 헤더 파일 경로 포함 (중요!)
# 이 설정이 있어야 native-lib.cpp에서 #include "KittyMemory.hpp"를 인식합니다.
target_include_directories(admin-logic PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/KittyMemory
)

# 5. 라이브러리 링크
# 빌드된 결과물에 안드로이드 시스템 로그와 기타 필수 라이브러리를 연결합니다.
target_link_libraries(admin-logic 
    ${log-lib} 
    android
)
