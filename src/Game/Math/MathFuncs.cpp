#include "MathFuncs.h"
#include "../../Core/Memory.h"
#include <iostream>

namespace GameHooks {

    constexpr uintptr_t ADDR_VECTOR_SUBTRACTION = 0x564A0;

    Vector3* __fastcall Vector_Subtraction(Vector3* base, void* edx_dummy, Vector3* subtraction)
    {
        base->x = base->x - subtraction->x;
        base->z = base->z - subtraction->z;
        base->y = base->y - subtraction->y;

        return base;
    }

    void InitMathHooks(uintptr_t gameBaseAddress) {
        uintptr_t absoluteAddr = gameBaseAddress + ADDR_VECTOR_SUBTRACTION;

        Memory::InstallHook(absoluteAddr, (void*)&Vector_Subtraction, 5);
    }
}