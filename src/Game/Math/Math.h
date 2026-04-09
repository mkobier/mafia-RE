#pragma once
#include <cstdint>

namespace Math 
{
    int __fastcall Random(int range);

    void InitHooks(uintptr_t gameBaseAddress);
}