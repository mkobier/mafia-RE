#pragma once
#include <cstdint>
#include "../Structs.h"

namespace GameHooks {
    void __fastcall Vector_Addition(Vector3* base, void* edx_dummy, Vector3* addition);
    Vector3* __fastcall Vector_Subtraction(Vector3* base, void* edx_dummy, Vector3* subtraction);
    void __fastcall Vector_Scale(Vector3* base, void* edx_dummy, float* scalar);
    void __fastcall Vector_Division(Vector3* base, void* edx_dummy, float scalar);

    void InitMathHooks(uintptr_t gameBaseAddress);
}