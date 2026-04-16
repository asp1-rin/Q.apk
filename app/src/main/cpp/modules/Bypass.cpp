#include "offset.h"
#include "KittyInclude.hpp"
#include <unistd.h>

// 보안 우회 로직 실행 함수
void ApplyBypass() {
    ProcMap xignMap;

    // libxigncode.so가 메모리에 로드될 때까지 대기
    while (!xignMap.isValid()) {
        xignMap = KittyMemory::getLibraryMap(S_LIB);
        usleep(500000); // 0.5초 대기
    }

    // 1. 심볼 이름으로 ZCWAVE_Notify 함수 찾기
    uintptr_t notifyAddr = KittyScanner::findSymbol(xignMap, "ZCWAVE_Notify");

    // 2. 심볼이 없으면 패턴 스캔으로 시도 (offsets.h에 정의된 패턴 사용)
    if (notifyAddr == 0) {
        notifyAddr = KittyScanner::findIdaPattern(xignMap, "FF 43 00 D1 F4 4F 01 A9"); 
    }

    // 3. 찾은 주소에 RET(강제 리턴) 명령어 패치
    if (notifyAddr != 0) {
        // ARM64 RET 명령어: 0xD65F03C0
        KittyMemory::write32(notifyAddr, 0xD65F03C0);
    }
}
