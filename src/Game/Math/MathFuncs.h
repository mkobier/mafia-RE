#pragma once
#include <cstdint>
#include "../Structs.h"

namespace GameHooks {
    void __fastcall Vector_Addition(Vector3* base, void* edx_dummy, Vector3* addition);
    Vector3* __fastcall Vector_Subtraction(Vector3* base, void* edx_dummy, Vector3* subtraction);

    void InitMathHooks(uintptr_t gameBaseAddress);
}