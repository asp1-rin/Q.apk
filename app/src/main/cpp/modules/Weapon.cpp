#include "offsets.h"
#include "KittyInclude.hpp"

// 패치 객체들을 전역으로 선언하여 상태 유지
KittyMemory::MemoryPatch recoilPatch;
KittyMemory::MemoryPatch spreadPatch;

// 초기 설정: 게임 라이브러리 로드 후 주소와 패치값 준비
void SetupWeapon() {
    // 무반동 패치 준비 (fmov s0, wzr)
    recoilPatch = KittyMemory::buildPatch(G_LIB, 0x33BFAF0, "\x00\x40\x20\x1E", 4);
    
    // 탄퍼짐 제거 패치 준비 (fmov s0, wzr)
    spreadPatch = KittyMemory::buildPatch(G_LIB, 0x35ADC9C, "\x00\x40\x20\x1E", 4);
}

// UI 스위치와 연결될 토글 함수
void ToggleNoRecoil(bool enable) {
    if (enable) recoilPatch.modify();
    else recoilPatch.restore();
}

void ToggleNoSpread(bool enable) {
    if (enable) spreadPatch.modify();
    else spreadPatch.restore();
}
