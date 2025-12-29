#include "Memory.h"

namespace Memory {
    void InstallHook(uintptr_t address, void* destination, size_t length) {
        DWORD oldProtect;
        VirtualProtect((void*)address, length, PAGE_EXECUTE_READWRITE, &oldProtect);

        DWORD relativeAddress = ((DWORD)destination - (DWORD)address) - 5;

        *(BYTE*)address = 0xE9; 
        *(DWORD*)(address + 1) = relativeAddress;

        for (size_t i = 5; i < length; i++) {
            *(BYTE*)(address + i) = 0x90;
        }

        FlushInstructionCache(GetCurrentProcess(), (void*)address, length);
        VirtualProtect((void*)address, length, oldProtect, &oldProtect);
    }
}