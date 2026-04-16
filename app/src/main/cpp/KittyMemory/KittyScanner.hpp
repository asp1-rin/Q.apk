#ifndef KITTYSCANNER_HPP
#define KITTYSCANNER_HPP

#include "KittyMemory.hpp"

namespace KittyScanner {
    // 함수 이름으로 주소 찾기 (ZCWAVE_Notify 등)
    uintptr_t findSymbol(ProcMap map, const char* symbol);
    
    // 바이트 패턴으로 주소 찾기
    uintptr_t findIdaPattern(ProcMap map, const char* pattern);
}

#endif
