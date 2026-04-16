#include "KittyScanner.hpp"
#include <sys/mman.h>
#include <string.h>

namespace KittyScanner {

    bool compare(const unsigned char *data, const unsigned char *pattern, const char *mask) {
        for (; *mask; ++mask, ++data, ++pattern) {
            if (*mask == 'x' && *data != *pattern)
                return false;
        }
        return (*mask == 0);
    }

    uintptr_t find_from_lib(const char *libName, const char *pattern, const char *mask) {
        ProcMap libMap = KittyMemory::getLibraryMap(libName);
        if (!libMap.isValid()) return 0;

        uintptr_t start = libMap.startAddress;
        uintptr_t end = libMap.endAddress;
        size_t len = strlen(mask);

        for (uintptr_t i = start; i < end - len; i++) {
            if (compare((unsigned char *)i, (const unsigned char *)pattern, mask))
                return i;
        }
        return 0;
    }

    // 링커 에러 해결을 위한 findSymbol 추가
    uintptr_t findSymbol(ProcMap libMap, const char *symbolName) {
        // 실제 심볼 테이블 파싱은 복잡하므로, 
        // 프로젝트 구성에 따라 적절한 심볼 로더나 dlsym을 활용하는 로직이 필요할 수 있습니다.
        // 여기서는 에러 방지를 위해 기본 반환값을 설정합니다.
        return 0; 
    }

    // 링커 에러 해결을 위한 findIdaPattern 추가
    uintptr_t findIdaPattern(ProcMap libMap, const char *pattern) {
        // IDA 스타일 패턴(예: "E8 ? ? ? ?")을 처리하는 로직을 여기에 구현합니다.
        // 현재는 링킹 에러를 해결하기 위한 틀만 제공합니다.
        return 0;
    }
}
