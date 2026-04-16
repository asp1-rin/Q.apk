# ASP1RIN ADMIN: Native Security Launcher

본 프로젝트는 고도의 보안이 요구되는 **관리자 전용 안드로이드 런처 및 네이티브 메모리 패치 엔진**입니다. 텅 빈 바닥 상태에서부터 정교한 C++ 엔진과 Kotlin UI를 결합하여 구축되었습니다.

---

## (Core Features)

### 1. 관리자 전용 인증 시스템
시스템 보안을 위해 사전 등록된 **6인의 관리자**만이 앱 기능을 활성화할 수 있습니다.
* **Access List**: ******

### 2. 네이티브 메모리 패치 엔진
`MJx0`의 `KittyMemory` 라이브러리를 기반으로 설계되어, 게임 프로세스의 메모리를 실시간으로 수정합니다.
* **Memory Patching**: `libMyGame.so` 라이브러리를 타겟팅하여 무반동(Recoil) 및 탄퍼짐(Spread) 방지 기능을 수행합니다.
* **Safe Injection**: 커스텀 JNI 계층을 통해 Java/Kotlin 레이어와 통신하며 보안성을 강화했습니다.

### 3. 실시간 제어 UI
로그인 성공 시에만 노출되는 대시보드를 통해 기능을 즉각적으로 ON/OFF 할 수 있습니다.

---

## (Tech Stack)

| 구분 | 기술 / 라이브러리 |
| :--- | :--- |
| **언어** | Kotlin (Frontend), C++11 (Backend) |
| **엔진** | KittyMemory (by MJx0) |
| **빌드 도구** | CMake, Gradle, Android NDK |
| **아키텍처** | JNI (Java Native Interface) |

---

## (Architecture)

* `app/build.gradle`: NDK 및 프로젝트 빌드 핵심 설정
* `app/src/main/cpp/`: 
    * `native-lib.cpp`: 메인 로직 및 패치 엔진
    * `CMakeLists.txt`: C++ 컴파일 가이드
    * `KittyMemory/`: 메모리 조작 라이브러리 소스
* `app/src/main/java/`: 관리자 인증 및 인터페이스 로직 (`MainActivity.kt`)

---

## ⚠️ 개발자 주의사항 (Notice)

1. **좌표 업데이트**: 현재 `native-lib.cpp`에 포함된 주소값(Offsets)은 예시용 더미 데이터입니다. 실제 운영 시 분석된 최신 좌표값으로 수정이 필요합니다.
2. **확장자 준수**: `KittyMemory`의 최신 규격에 따라 모든 헤더는 `.hpp` 확장자를 참조합니다.
3. **권한**: 오버레이 창이나 메모리 접근을 위해 안드로이드 권한 설정이 필요할 수 있습니다.

---
**© 2026 ASP1RIN. All Rights Reserved.**
