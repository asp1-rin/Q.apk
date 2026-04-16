#include "offsets.h"

// 패치 객체 생성
KittyMemory::MemoryPatch recoilPatch;

void SetupWeapon() {
    ProcMap gameMap = KittyMemory::getLibraryMap(G_LIB);
    if(gameMap.isValid()) {
        // 주소에 fmov s0, wzr (0x1E204000) 패치 준비
        recoilPatch = KittyMemory::buildPatch(G_LIB, offsets.no_recoil, "\x00\x40\x20\x1E", 4);
    }
}

void ToggleNoRecoil(bool enable) {
    if (enable) recoilPatch.modify(); // 패치 적용
    else recoilPatch.restore();      // 원본 복구
}
