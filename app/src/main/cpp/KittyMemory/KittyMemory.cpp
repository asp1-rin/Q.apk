#include "KittyMemory.hpp"
#include <fstream>
#include <sstream>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>

namespace KittyMemory {
    ProcMap getLibraryMap(const char *libName) {
        ProcMap m;
        m.startAddress = 0;
        m.endAddress = 0;
        char line[512];
        FILE *f = fopen("/proc/self/maps", "r");
        if (!f) return m;

        while (fgets(line, sizeof(line), f)) {
            if (strstr(line, libName)) {
                uintptr_t start, end;
                sscanf(line, "%lx-%lx", &start, &end);
                m.startAddress = start;
                m.endAddress = end;
                m.length = end - start;
                m.pathname = libName;
                break;
            }
        }
        fclose(f);
        return m;
    }

    // MemoryPatch 구현부 추가
    MemoryPatch MemoryPatch::buildPatch(const char* libName, uintptr_t offset, const char* patchCode, size_t patchSize) {
        MemoryPatch patch;
        ProcMap map = getLibraryMap(libName);
        if (map.isValid()) {
            patch._address = map.startAddress + offset;
            patch._size = patchSize;
            patch._patchBytes.assign(patchCode, patchCode + patchSize);
            
            // 원본 데이터 보관
            patch._origBytes.resize(patchSize);
            memcpy(patch._origBytes.data(), (void*)patch._address, patchSize);
        }
        return patch;
    }

    bool MemoryPatch::modify() {
        if (_address == 0) return false;
        uintptr_t pageStart = _address & ~0xFFF;
        mprotect((void *)pageStart, 0x1000 * 2, PROT_READ | PROT_WRITE | PROT_EXEC);
        memcpy((void*)_address, _patchBytes.data(), _size);
        return true;
    }

    bool MemoryPatch::restore() {
        if (_address == 0) return false;
        uintptr_t pageStart = _address & ~0xFFF;
        mprotect((void *)pageStart, 0x1000 * 2, PROT_READ | PROT_WRITE | PROT_EXEC);
        memcpy((void*)_address, _origBytes.data(), _size);
        return true;
    }

    bool write32(uintptr_t address, uint32_t value) {
        mprotect((void *)(address & ~0xFFF), 0x1000 * 2, PROT_READ | PROT_WRITE | PROT_EXEC);
        *(uint32_t *)address = value;
        return true;
    }
}
