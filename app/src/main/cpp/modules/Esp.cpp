#include "offsets.h"
#include "KittyInclude.hpp"

struct EnemyData {
    float x, y, z;
    int health;
    bool isVisible;
};

// 적들의 정보를 한 번에 긁어모아 UI(Java) 레이어로 전달하기 위한 함수
void GetEnemyLocations(uintptr_t enemyManager, EnemyData outData[], int maxEnemies) {
    if (!enemyManager) return;

    for (int i = 0; i < maxEnemies; i++) {
        // 엔티티 리스트 구조를 따라 적 포인터 획득
        uintptr_t enemy = *(uintptr_t*)(enemyManager + (i * 0x8)); 
        
        if (enemy) {
            outData[i].x = *(float*)(enemy + 0x190);
            outData[i].y = *(float*)(enemy + 0x194);
            outData[i].z = *(float*)(enemy + 0x198);
            outData[i].health = *(int*)(enemy + 0x2C);
            // 이 데이터를 Java의 Canvas나 Overlay View로 넘겨서 박스를 그림
        }
    }
}
