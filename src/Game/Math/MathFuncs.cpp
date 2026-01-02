#include "MathFuncs.h"
#include "../../Core/Memory.h"
#include <iostream>

namespace GameHooks {

    constexpr uintptr_t ADDR_VECTOR_ADDITION = 0xBA00;
    constexpr uintptr_t ADDR_VECTOR_SUBTRACTION = 0x564A0;
    
    void __fastcall Vector_Addition(Vector3* base, void* edx_dummy, Vector3* addition)
    {
        base->x = base->x + addition->x;
        base->z = base->z + addition->z;
        base->y = base->y + addition->y;
    }

    Vector3* __fastcall Vector_Subtraction(Vector3* base, void* edx_dummy, Vector3* subtraction)
    {
        base->x = base->x - subtraction->x;
        base->z = base->z - subtraction->z;
        base->y = base->y - subtraction->y;

        return base;
    }

    void InitMathHooks(uintptr_t gameBaseAddress) {
        uintptr_t absoluteAddrAdd = gameBaseAddress + ADDR_VECTOR_ADDITION;
        Memory::InstallHook(absoluteAddrAdd, (void*)&Vector_Addition, 5);

        uintptr_t absoluteAddrSub = gameBaseAddress + ADDR_VECTOR_SUBTRACTION;
        Memory::InstallHook(absoluteAddrSub, (void*)&Vector_Subtraction, 5);
    }
}