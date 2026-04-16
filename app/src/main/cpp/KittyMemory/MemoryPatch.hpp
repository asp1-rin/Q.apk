#ifndef MEMORYPATCH_HPP
#define MEMORYPATCH_HPP

#include <vector>
#include <stdint.h>
#include "KittyMemory.hpp"

namespace KittyMemory {
    class MemoryPatch {
    public:
        MemoryPatch() : _address(0), _size(0) {}
        
        static MemoryPatch buildPatch(const char* libName, uintptr_t offset, const char* patchCode, size_t patchSize);
        
        bool modify();  // 패치 적용
        bool restore(); // 원본 복구

    private:
        uintptr_t _address;
        size_t _size;
        std::vector<uint8_t> _origBytes;
        std::vector<uint8_t> _patchBytes;
    };
}

#endif
