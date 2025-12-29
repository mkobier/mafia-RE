#pragma once
#include <windows.h>
#include <cstdint>

namespace Memory {
    void InstallHook(uintptr_t address, void* destination, size_t length);
}