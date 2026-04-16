#ifndef OFFSETS_H
#define OFFSETS_H
#include "KittyMemory/KittyInclude.hpp"

// 게임 라이브러리 이름
#define G_LIB "libMyGame.so"
#define S_LIB "libxigncode.so"

struct Offsets {
    // Bypass (심볼 또는 패턴)
    const char* sym_notify = "ZCWAVE_Notify";
    
    // Weapon (xaOffset)
    uintptr_t no_recoil = 0x33BFAF0;
    uintptr_t no_spread = 0x35ADC9C;
    
    // Aimbot (eposOffset)
    uintptr_t player_base = 0x7ABE28;
    uintptr_t posX = 0x190;
    uintptr_t posY = 0x194;
    uintptr_t posZ = 0x198;
};

extern Offsets offsets;
#endif
