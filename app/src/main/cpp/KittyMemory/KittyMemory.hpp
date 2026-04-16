#ifndef KITTYMEMORY_HPP
#define KITTYMEMORY_HPP

#include <string>
#include <vector>
#include <stdint.h>

struct ProcMap {
    uintptr_t startAddress;
    uintptr_t endAddress;
    size_t length;
    std::string pathname;
    bool isValid() const { return startAddress != 0 && endAddress != 0; }
};

namespace KittyMemory {
    // 라이브러리 주소 찾기
    ProcMap getLibraryMap(const char *libName);
    
    // 메모리에 데이터 쓰기 (권한 자동 처리)
    bool write64(uintptr_t address, uint64_t value);
    bool write32(uintptr_t address, uint32_t value);
}

#endif
