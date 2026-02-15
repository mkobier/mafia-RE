#include "Vector3.h"
#include "../../Core/Memory.h"
#include <iostream>

namespace GameHooks 
{

    constexpr uintptr_t ADDR_VECTOR_ADDITION = 0xAE00;
    constexpr uintptr_t ADDR_VECTOR_ADDITION_SIMPLE = 0xBA00;
    constexpr uintptr_t ADDR_VECTOR_SUBTRACTION = 0x7540;
    constexpr uintptr_t ADDR_VECTOR_SUBTRACTION_SIMPLE = 0x564A0;
    constexpr uintptr_t ADDR_VECTOR_SCALE = 0xADD0;
    constexpr uintptr_t ADDR_VECTOR_SCALE_SIMPLE = 0xB9E0;
    constexpr uintptr_t ADDR_VECTOR_DIVISION = 0xF9BB0;
    constexpr uintptr_t ADDR_VECTOR_SQUARED_LENGTH = 0x564D0;
    constexpr uintptr_t ADDR_VECTOR_COPY_COORDINATES = 0x2A30;
    constexpr uintptr_t ADDR_VECTOR_COPY = 0x38EE0;
    
    Vector3* __fastcall Vector_Addition(Vector3* base, void* edx_dummy, Vector3* result, Vector3* addition)
    {
        result->x = base->x + addition->x;
        result->z = base->z + addition->z;
        result->y = base->y + addition->y;

        return result;
    }

    void __fastcall Vector_Addition_Simple(Vector3* base, void* edx_dummy, Vector3* addition)
    {
        base->x = base->x + addition->x;
        base->z = base->z + addition->z;
        base->y = base->y + addition->y;
    }

    Vector3* __fastcall Vector_Subtraction(Vector3* base, void* edx_dummy, Vector3* result, Vector3* subtraction)
    {
        result->x = base->x - subtraction->x;
        result->y = base->y - subtraction->y;
        result->z = base->z - subtraction->z;

        return result;
    }

    Vector3* __fastcall Vector_Subtraction_Simple(Vector3* base, void* edx_dummy, Vector3* subtraction)
    {
        base->x = base->x - subtraction->x;
        base->z = base->z - subtraction->z;
        base->y = base->y - subtraction->y;

        return base;
    }

    Vector3* __fastcall Vector_Scale(Vector3* source, void* edx_dummy, Vector3* result, float* scalar)
    {
        float s = *scalar;

        result->x = s * source->x;
        result->z = s * source->z;
        result->y = s * source->y;

        return result;
    }

    void __fastcall Vector_Scale_Simple(Vector3* base, void* edx_dummy, float* scalar)
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

    Vector3* __fastcall Vector_CopyCoordinates(Vector3* base, void* edx_dummy, float x, float z, float y)
    {
        base->x = x;
        base->z = z;
        base->y = y;

        return base;
    }

    Vector3* __fastcall Vector_Copy(Vector3* src, void* edx_dummy, Vector3* dest)
    {
        dest->x = src->x;
        dest->z = src->z;
        dest->y = src->y;

        return dest;
    }

    void InitVector3Hooks(uintptr_t gameBaseAddress) 
    {
        uintptr_t absoluteAddrAdd = gameBaseAddress + ADDR_VECTOR_ADDITION;
        Memory::InstallHook(absoluteAddrAdd, (void*)&Vector_Addition, 5);

        uintptr_t absoluteAddrAddS = gameBaseAddress + ADDR_VECTOR_ADDITION_SIMPLE;
        Memory::InstallHook(absoluteAddrAddS, (void*)&Vector_Addition_Simple, 5);

        uintptr_t absoluteAddrSub = gameBaseAddress + ADDR_VECTOR_SUBTRACTION;
        Memory::InstallHook(absoluteAddrSub, (void*)&Vector_Subtraction, 5);

        uintptr_t absoluteAddrSubS = gameBaseAddress + ADDR_VECTOR_SUBTRACTION_SIMPLE;
        Memory::InstallHook(absoluteAddrSubS, (void*)&Vector_Subtraction_Simple, 5);

        uintptr_t absoluteAddrMul = gameBaseAddress + ADDR_VECTOR_SCALE;
        Memory::InstallHook(absoluteAddrMul, (void*)&Vector_Scale, 5);

        uintptr_t absoluteAddrMulS = gameBaseAddress + ADDR_VECTOR_SCALE_SIMPLE;
        Memory::InstallHook(absoluteAddrMulS, (void*)&Vector_Scale_Simple, 5);

        uintptr_t absoluteAddrDiv = gameBaseAddress + ADDR_VECTOR_DIVISION;
        Memory::InstallHook(absoluteAddrDiv, (void*)&Vector_Division, 5);

        uintptr_t absoluteAddrSqLen = gameBaseAddress + ADDR_VECTOR_SQUARED_LENGTH;
        Memory::InstallHook(absoluteAddrSqLen, (void*)&Vector_SquaredLength, 5);

        uintptr_t absoluteAddrCopyCoords = gameBaseAddress + ADDR_VECTOR_COPY_COORDINATES;
        Memory::InstallHook(absoluteAddrCopyCoords, (void*)&Vector_CopyCoordinates, 5);

        uintptr_t absoluteAddrCopy = gameBaseAddress + ADDR_VECTOR_COPY;
        Memory::InstallHook(absoluteAddrCopy, (void*)&Vector_Copy, 5);
    }
}