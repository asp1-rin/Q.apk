#include "offset.h"
#include "MemoryPatch.hpp"

KittyMemory::MemoryPatch recoilPatch;
KittyMemory::MemoryPatch spreadPatch;

void initWeaponPatches() {
    const char* G_LIB = "libUE4.so";

    recoilPatch = KittyMemory::MemoryPatch::buildPatch(G_LIB, 0x33BFAF0, "\x00\x40\x20\x1E", 4);
    spreadPatch = KittyMemory::MemoryPatch::buildPatch(G_LIB, 0x35ADC9C, "\x00\x40\x20\x1E", 4);
}

void setWeaponPatch(bool enable) {
    if (enable) {
        recoilPatch.modify();
        spreadPatch.modify();
    } else {
        recoilPatch.restore();
        spreadPatch.restore();
    }
}
