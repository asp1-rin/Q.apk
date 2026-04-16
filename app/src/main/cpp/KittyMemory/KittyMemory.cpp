#include "KittyMemory.h"
#include <fstream>
#include <sstream>
#include <sys/mman.h>

namespace KittyMemory {
    ProcMap getLibraryMap(const char *libName) {
        ProcMap m;
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

    bool write32(uintptr_t address, uint32_t value) {
        mprotect((void *)(address & ~0xFFF), 0x1000 * 2, PROT_READ | PROT_WRITE | PROT_EXEC);
        *(uint32_t *)address = value;
        return true;
    }
}
