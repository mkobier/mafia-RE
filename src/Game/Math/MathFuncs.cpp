#include "MathFuncs.h"
#include "../../Core/Memory.h"
#include <iostream>

namespace GameHooks 
{

    constexpr uintptr_t ADDR_VECTOR_ADDITION = 0xBA00;
    constexpr uintptr_t ADDR_VECTOR_SUBTRACTION = 0x564A0;
    constexpr uintptr_t ADDR_VECTOR_SCALE = 0xB9E0;
    constexpr uintptr_t ADDR_VECTOR_DIVISION = 0xF9BB0;
    constexpr uintptr_t ADDR_VECTOR_SQUARED_LENGTH = 0x564D0;
    
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

    void __fastcall Vector_Scale(Vector3* base, void* edx_dummy, float* scalar)
    {
        float s = *scalar;

        base->x = s * base->x;
        base->z = s * base->z;
        base->y = s * base->y;
    }

    void __fastcall Vector_Division(Vector3* base, void* edx_dummy, float scalar)
    {
        float s = 1.0f / scalar;

        base->x = s * base->x;
        base->z = s * base->z;
        base->y = s * base->y;
    }

    double __fastcall Vector_SquaredLength(Vector3* base, void* edx_dummy)
    {
        return (double)(base->x * base->x) + (double)(base->z * base->z) + (double)(base->y * base->y);
    }

    void InitMathHooks(uintptr_t gameBaseAddress) 
    {
        uintptr_t absoluteAddrAdd = gameBaseAddress + ADDR_VECTOR_ADDITION;
        Memory::InstallHook(absoluteAddrAdd, (void*)&Vector_Addition, 5);

        uintptr_t absoluteAddrSub = gameBaseAddress + ADDR_VECTOR_SUBTRACTION;
        Memory::InstallHook(absoluteAddrSub, (void*)&Vector_Subtraction, 5);

        uintptr_t absoluteAddrMul = gameBaseAddress + ADDR_VECTOR_SCALE;
        Memory::InstallHook(absoluteAddrMul, (void*)&Vector_Scale, 5);

        uintptr_t absoluteAddrDiv = gameBaseAddress + ADDR_VECTOR_DIVISION;
        Memory::InstallHook(absoluteAddrDiv, (void*)&Vector_Division, 5);

        uintptr_t absoluteAddrSqLen = gameBaseAddress + ADDR_VECTOR_SQUARED_LENGTH;
        Memory::InstallHook(absoluteAddrSqLen, (void*)&Vector_SquaredLength, 5);
    }
}