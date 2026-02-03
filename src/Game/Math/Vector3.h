#pragma once
#include <cstdint>

struct Vector3
{
    float x;
    float z;
    float y;
};

namespace GameHooks {
    void __fastcall Vector_Addition_Simple(Vector3* base, void* edx_dummy, Vector3* addition);
    Vector3* __fastcall Vector_Subtraction_Simple(Vector3* base, void* edx_dummy, Vector3* subtraction);
    void __fastcall Vector_Scale(Vector3* base, void* edx_dummy, float* scalar);
    void __fastcall Vector_Division(Vector3* base, void* edx_dummy, float scalar);
    double __fastcall Vector_SquaredLength(Vector3* base, void* edx_dummy);
    Vector3* __fastcall Vector_Addition(Vector3* base, void* edx_dummy, Vector3* result, Vector3* addition);
    Vector3* __fastcall Vector_Subtraction(Vector3* base, void* edx_dummy, Vector3* result, Vector3* subtraction);

    void InitVector3Hooks(uintptr_t gameBaseAddress);
}