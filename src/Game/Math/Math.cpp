#include "Math.h"
#include "../../Core/Memory.h"
#include <cstdlib> 

constexpr uintptr_t ADDR_RANDOM = 0x8450;

namespace Math 
{
    int __fastcall Random(int range)
    {
        if (range >= 1)
        {
            return rand() % range;
        }
        return 0;
    }

    void InitHooks(uintptr_t gameBaseAddress)
    {

        Memory::InstallHook(gameBaseAddress + ADDR_RANDOM,(void*)&Random, 5);
    }
}