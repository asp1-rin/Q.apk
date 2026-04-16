#include "offsets.h"
#include "KittyInclude.hpp"

// 적 정보를 담을 구조체 (제공된 오프셋 반영)
struct EnemyInfo {
    float x, y, z;          // 위치 (0x190, 0x194, 0x198)
    int hp;                 // 현재 체력 (0x2C)
    int maxHp;              // 최대 체력 (0xEF4)
    char nickname[11];      // 닉네임 (0x88)
    int state;              // 상태 (0x12C) - 생존 여부 확인용
    int weapon;             // 들고 있는 무기 (0x2E)
};

void GetAdvancedEnemyData(uintptr_t enemyManager, EnemyInfo outData[], int maxEnemies) {
    if (!enemyManager) return;

    for (int i = 0; i < maxEnemies; i++) {
        // 엔티티 리스트에서 적 포인터 읽기
        uintptr_t enemyPtr = *(uintptr_t*)(enemyManager + (i * 0x8));
        
        if (enemyPtr) {
            // 위치 데이터 (float)
            outData[i].x = *(float*)(enemyPtr + 0x190);
            outData[i].y = *(float*)(enemyPtr + 0x194);
            outData[i].z = *(float*)(enemyPtr + 0x198);

            // 체력 데이터 (int16, int32)
            outData[i].hp = *(int16_t*)(enemyPtr + 0x2C);
            outData[i].maxHp = *(int32_t*)(enemyPtr + 0xEF4);

            // 상태 및 무기
            outData[i].state = *(uint8_t*)(enemyPtr + 0x12C);
            outData[i].weapon = *(int16_t*)(enemyPtr + 0x2E);

            // 닉네임 복사 (문자열)
            memcpy(outData[i].nickname, (void*)(enemyPtr + 0x88), 10);
            outData[i].nickname[10] = '\0';
        }
    }
}
