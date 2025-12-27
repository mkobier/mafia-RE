#include <windows.h>
#include <cstdint>
#include <iostream>

#pragma pack(push, 1)
struct Vector3 
{
    float x;
    float z;
    float y;
};

Vector3* __fastcall Vector_Subtraction(Vector3* base, void* edx_dummy, Vector3* subtraction) 
{

    base->x = base->x - subtraction->x;
    base->z = base->z - subtraction->z;
    base->y = base->y - subtraction->y;

    return base;
}

void InstallHook(uintptr_t address, void* destination, size_t length) {
    DWORD oldProtect;
    VirtualProtect((void*)address, length, PAGE_EXECUTE_READWRITE, &oldProtect);
    DWORD relativeAddress = ((DWORD)destination - (DWORD)address) - 5;

    *(BYTE*)address = 0xE9;
    *(DWORD*)(address + 1) = relativeAddress;

    for (size_t i = 5; i < length; i++) {
        *(BYTE*)(address + i) = 0x90;
    }

    FlushInstructionCache(GetCurrentProcess(), (void*)address, length);
    VirtualProtect((void*)address, length, oldProtect, &oldProtect);
}

DWORD WINAPI MainThread(LPVOID lpParam) {
    HMODULE hGame = GetModuleHandle(NULL);
    if (hGame) {
        uintptr_t address_vector_subtraction = (uintptr_t)hGame + 0x564A0;
        InstallHook(address_vector_subtraction, (void*)&Vector_Subtraction, 5);
    }
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, MainThread, hModule, 0, NULL);
    }
    return TRUE;
}
