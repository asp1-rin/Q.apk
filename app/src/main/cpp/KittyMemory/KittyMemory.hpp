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
    ProcMap getLibraryMap(const char *libName);
    bool write64(uintptr_t address, uint64_t value);
    bool write32(uintptr_t address, uint32_t value);


    class MemoryPatch {
    public:
        MemoryPatch() : _address(0), _size(0) {}
        static MemoryPatch buildPatch(const char* libName, uintptr_t offset, const char* patchCode, size_t patchSize);
        bool modify();
        bool restore();
    private:
        uintptr_t _address;
        size_t _size;
        std::vector<char> _origBytes;
        std::vector<char> _patchBytes;
    };
}

#endif
