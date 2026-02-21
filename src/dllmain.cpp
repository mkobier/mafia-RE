#include <windows.h>
#include "Game/Math/Vector3.h"

DWORD WINAPI MainThread(LPVOID lpParam) {
    HMODULE hGame = GetModuleHandle(NULL);

    if (hGame) {
        uintptr_t baseAddress = (uintptr_t)hGame;

        Vector3::InitHooks(baseAddress);
    }

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, 0, MainThread, hModule, 0, NULL);
    }
    return TRUE;
}