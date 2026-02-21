#pragma once
#include <windows.h>
#include <cstdint>

template<typename T>
void* FindFunctionAdress(T method) {
    union {
        T m;
        void* p;
    } u;
    u.m = method;
    return u.p;
}

namespace Memory {
    void InstallHook(uintptr_t address, void* destination, size_t length);
}