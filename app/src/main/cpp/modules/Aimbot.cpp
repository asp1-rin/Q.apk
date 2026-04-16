#include "offsets.h"
#include "KittyInclude.hpp"
#include <cmath>

// 사용자가 UI에서 조절할 설정 변수들
float aimbotFov = 20.0f;        // 에임봇이 작동할 화면 중앙 원의 크기
float aimbotSmooth = 4.0f;      // 값이 낮을수록 자석처럼 강하게 붙음 (1.0 = 즉시 고정)
bool isAimbotEnabled = false;   

#define PI 3.14159265358979323846

// 각도 계산을 위한 수학 유틸리티
float Deg2Rad(float deg) { return deg * (PI / 180.0f); }
float Rad2Deg(float rad) { return rad * (180.0f / PI); }

// 두 각도 사이의 최단 거리 계산 (360도 경계 처리)
float GetAngleDiff(float angle1, float angle2) {
    float diff = fmod(angle2 - angle1 + 180.0f, 360.0f) - 180.0f;
    return (diff < -180.0f) ? diff + 360.0f : diff;
}

// 에임봇 메인 루프 (게임 렌더링 스레드 혹은 별도 루프에서 호출)
void UpdateAimbot(uintptr_t localPlayer, uintptr_t enemyList[], int enemyCount) {
    if (!isAimbotEnabled || !localPlayer) return;

    // 1. 카메라 데이터 접근 (제공해주신 _anOffset 적용)
    ProcMap gameMap = KittyMemory::getLibraryMap(G_LIB);
    if (!gameMap.isValid()) return;

    // 카메라 베이스 주소 (0x8B26DC)
    uintptr_t cameraBaseAddr = gameMap.startAddress + 0x8B26DC;
    
    // 현재 카메라 각도 읽기 (Pitch: +0x0, Yaw: +0x4)
    float currentPitch = *(float*)(cameraBaseAddr + 0x0);
    float currentYaw = *(float*)(cameraBaseAddr + 0x4);

    // 2. 내 위치 읽기 (제공해주신 _eposOffset: x=0x190, y=0x194, z=0x198)
    float myX = *(float*)(localPlayer + 0x190);
    float myY = *(float*)(localPlayer + 0x194);
    float myZ = *(float*)(localPlayer + 0x198);

    float minDistance = 99999.0f;
    uintptr_t targetEnemy = 0;
    float targetYaw = 0, targetPitch = 0;

    // 3. 주변 적들 스캔
    for (int i = 0; i < enemyCount; i++) {
        uintptr_t enemy = enemyList[i];
        
        // 유효성 검사 (죽은 적 제외 - _eposOffset 'state': 0x12C 활용)
        if (!enemy || *(uint8_t*)(enemy + 0x12C) <= 0) continue;
        
        // 체력 확인 (HP: 0x2C)
        if (*(int16_t*)(enemy + 0x2C) <= 0) continue;

        // 적 위치 및 머리 높이 보정 (+1.8f는 캐릭터 모델링에 따른 예상값)
        float enX = *(float*)(enemy + 0x190);
        float enY = *(float*)(enemy + 0x194) + 1.8f; 
        float enZ = *(float*)(enemy + 0x198);

        // 거리 및 각도 차이 계산
        float dx = enX - myX;
        float dy = enY - myY;
        float dz = enZ - myZ;
        float horizontalDist = sqrt(dx * dx + dz * dz);
        float dist = sqrt(dx * dx + dy * dy + dz * dz);

        // 적을 바라보기 위해 필요한 절대 각도 (atan2 사용)
        float neededYaw = Rad2Deg(atan2(dz, dx));
        float neededPitch = Rad2Deg(atan2(dy, horizontalDist));

        // 4. FOV(시야 원) 체크: 현재 조준점과 적 사이의 각도 차이 계산
        float yawDiff = abs(GetAngleDiff(currentYaw, neededYaw));
        float pitchDiff = abs(GetAngleDiff(currentPitch, neededPitch));
        float totalFovDiff = sqrt(yawDiff * yawDiff + pitchDiff * pitchDiff);

        // 설정된 FOV 원 안에 적이 있을 경우에만 타겟팅
        if (totalFovDiff <= aimbotFov) {
            if (dist < minDistance) {
                minDistance = dist;
                targetEnemy = enemy;
                targetYaw = neededYaw;
                targetPitch = neededPitch;
            }
        }
    }

    // 5. 자석 에임(Magnet) 적용: 카메라 각도를 부드럽게 타겟 쪽으로 이동
    if (targetEnemy != 0) {
        // Smoothing 로직: 한 번에 고정하지 않고 aimbotSmooth 값에 따라 조금씩 이동
        float finalYaw = currentYaw + GetAngleDiff(currentYaw, targetYaw) / aimbotSmooth;
        float finalPitch = currentPitch + GetAngleDiff(currentPitch, targetPitch) / aimbotSmooth;

        // 실제 카메라 메모리에 각도 주입
        *(float*)(cameraBaseAddr + 0x0) = finalPitch; // Pitch 업데이트
        *(float*)(cameraBaseAddr + 0x4) = finalYaw;   // Yaw 업데이트
    }
}

// --- Java UI 연동을 위한 JNI 함수 ---
extern "C" JNIEXPORT void JNICALL
Java_com_example_milkchoco_MainActivity_setAimbotState(JNIEnv* env, jobject thiz, jboolean enable) {
    isAimbotEnabled = enable;
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_milkchoco_MainActivity_setAimbotFov(JNIEnv* env, jobject thiz, jfloat fov) {
    aimbotFov = fov;
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_milkchoco_MainActivity_setAimbotSmooth(JNIEnv* env, jobject thiz, jfloat smooth) {
    aimbotSmooth = (smooth < 1.0f) ? 1.0f : smooth; // 최소값 1.0 보장
}
