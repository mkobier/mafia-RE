#include "Vector3.h"
#include "../../Core/Memory.h"
#include <iostream>

namespace GameHooks 
{

    constexpr uintptr_t ADDR_VECTOR_ADDITION_SIMPLE = 0xBA00;
    constexpr uintptr_t ADDR_VECTOR_SUBTRACTION_SIMPLE = 0x564A0;
    constexpr uintptr_t ADDR_VECTOR_SCALE = 0xB9E0;
    constexpr uintptr_t ADDR_VECTOR_DIVISION = 0xF9BB0;
    constexpr uintptr_t ADDR_VECTOR_SQUARED_LENGTH = 0x564D0;
    constexpr uintptr_t ADDR_VECTOR_ADDITION = 0xAE00;
    constexpr uintptr_t ADDR_VECTOR_SUBTRACTION = 0x7540;
    
    void __fastcall Vector_Addition_Simple(Vector3* base, void* edx_dummy, Vector3* addition)
    {
        base->x = base->x + addition->x;
        base->z = base->z + addition->z;
        base->y = base->y + addition->y;
    }

    Vector3* __fastcall Vector_Subtraction_Simple(Vector3* base, void* edx_dummy, Vector3* subtraction)
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

    Vector3* __fastcall Vector_Addition(Vector3* base, void* edx_dummy, Vector3* result, Vector3* addition)
    {
        result->x = base->x + addition->x;
        result->z = base->z + addition->z;
        result->y = base->y + addition->y;

        return result;
    }

    Vector3* __fastcall Vector_Subtraction(Vector3* base, void* edx_dummy, Vector3* result, Vector3* subtraction)
    {
        result->x = base->x - subtraction->x;
        result->y = base->y - subtraction->y;
        result->z = base->z - subtraction->z;

        return result;
    }

    void InitVector3Hooks(uintptr_t gameBaseAddress) 
    {
        uintptr_t absoluteAddrAddS = gameBaseAddress + ADDR_VECTOR_ADDITION_SIMPLE;
        Memory::InstallHook(absoluteAddrAddS, (void*)&Vector_Addition_Simple, 5);

        uintptr_t absoluteAddrSubS = gameBaseAddress + ADDR_VECTOR_SUBTRACTION_SIMPLE;
        Memory::InstallHook(absoluteAddrSubS, (void*)&Vector_Subtraction_Simple, 5);

        uintptr_t absoluteAddrMul = gameBaseAddress + ADDR_VECTOR_SCALE;
        Memory::InstallHook(absoluteAddrMul, (void*)&Vector_Scale, 5);

        uintptr_t absoluteAddrDiv = gameBaseAddress + ADDR_VECTOR_DIVISION;
        Memory::InstallHook(absoluteAddrDiv, (void*)&Vector_Division, 5);

        uintptr_t absoluteAddrSqLen = gameBaseAddress + ADDR_VECTOR_SQUARED_LENGTH;
        Memory::InstallHook(absoluteAddrSqLen, (void*)&Vector_SquaredLength, 5);

        uintptr_t absoluteAddrAdd = gameBaseAddress + ADDR_VECTOR_ADDITION;
        Memory::InstallHook(absoluteAddrAdd, (void*)&Vector_Addition, 5);

        uintptr_t absoluteAddrSub = gameBaseAddress + ADDR_VECTOR_SUBTRACTION;
        Memory::InstallHook(absoluteAddrSub, (void*)&Vector_Subtraction, 5);
    }
}