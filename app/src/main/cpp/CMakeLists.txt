# 최소 요구 CMake 버전
cmake_minimum_required(VERSION 3.18.1)

# 프로젝트 이름 설정
project("q_launcher")

# 1. KittyMemory 라이브러리 포함
# 이 폴더 안에 자체 CMakeLists.txt가 있어야 하며, 이를 빌드 과정에 포함시킵니다.
add_subdirectory(KittyMemory)

# 2. 메인 네이티브 라이브러리 생성
# native-lib.cpp를 컴파일하여 native-lib이라는 이름의 공유 라이브러리(.so)를 만듭니다.
add_library(
        native-lib
        SHARED
        native-lib.cpp
)

# 3. 안드로이드 로그 라이브러리 찾기
# C++ 코드에서 __android_log_print 등을 사용하기 위해 필요합니다.
find_library(
        log-lib
        log
)

# 4. 모든 라이브러리 연결 (Link)
# 메인 라이브러리에 KittyMemory와 로그 라이브러리를 하나로 묶습니다.
target_link_libraries(
        native-lib
        KittyMemory
        ${log-lib}
)
