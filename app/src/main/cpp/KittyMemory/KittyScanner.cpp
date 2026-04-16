#include "KittyScanner.hpp"
#include <sys/mman.h>

namespace KittyScanner {

    bool compare(const unsigned char *data, const unsigned char *pattern, const char *mask) {
        for (; *mask; ++mask, ++data, ++pattern) {
            if (*mask == 'x' && *data != *pattern)
                return false;
        }
        return (*mask == 0);
    }

    uintptr_t find_from_lib(const char *libName, const char *pattern, const char *mask) {
        ProcMap libMap;
        if (!KittyMemory::getLibraryMap(libName, libMap)) return 0;

        uintptr_t start = libMap.startAddress;
        uintptr_t end = libMap.endAddress;
        size_t len = strlen(mask);

        for (uintptr_t i = start; i < end - len; i++) {
            if (compare((unsigned char *)i, (const unsigned char *)pattern, mask))
                return i;
        }
        return 0;
    }
}
