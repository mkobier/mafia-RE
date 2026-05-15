#pragma once
#include <cstdint>
#include <cmath>
#include "../Math/Vector3.h"

namespace Physics
{
    long double __stdcall CheckSphereIntersection(Vector3* position1, Vector3* velocity1, float radius1, Vector3* position2, Vector3* velocity2, float radius2);

    void InitHooks(uintptr_t gameBaseAddress);
}