#include "offsets.h"

void ApplyBypass() {
    // libxigncode.so가 로드될 때까지 대기 후 주소 획득
    ProcMap xignMap;
    do {
        xignMap = KittyMemory::getLibraryMap(S_LIB);
        sleep(1);
    } while (!xignMap.isValid());

    // ZCWAVE_Notify 함수 찾기 및 패치
    uintptr_t notifyAddr = KittyScanner::findSymbol(xignMap, offsets.sym_notify);
    
    if (notifyAddr != 0) {
        // KittyMemory의 patch 기능을 사용하여 RET 명령어 주입
        // ARM64 RET: 0xC0035FD6
        KittyMemory::write64(notifyAddr, 0xD65F03C0); 
    }
}
