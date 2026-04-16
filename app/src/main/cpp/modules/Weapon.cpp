#include "offset.h"
#include "MemoryPatch.hpp"

KittyMemory::MemoryPatch recoilPatch;
KittyMemory::MemoryPatch spreadPatch;

void SetupWeapon() {
    recoilPatch = KittyMemory::MemoryPatch::buildPatch(G_LIB, 0x33BFAF0, "\x00\x40\x20\x1E", 4);
    spreadPatch = KittyMemory::MemoryPatch::buildPatch(G_LIB, 0x35ADC9C, "\x00\x40\x20\x1E", 4);
}

void ToggleNoRecoil(bool enable) {
    if (enable) recoilPatch.modify();
    else recoilPatch.restore();
}

void ToggleNoSpread(bool enable) {
    if (enable) spreadPatch.modify();
    else spreadPatch.restore();
}
