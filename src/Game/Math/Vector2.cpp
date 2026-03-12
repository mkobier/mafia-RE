#include "Vector2.h"
#include "../../Core/Memory.h"
#include <iostream>

Vector2* Vector2::Sum(Vector2* result, Vector2* addition)
{
    result->x = this->x + addition->x;
    result->y = this->y + addition->y;

    return result;
}

void Vector2::InitHooks(uintptr_t gameBaseAddress)
{
    Memory::InstallHook(gameBaseAddress + ADDR_VECTOR_SUM, FindFunctionAdress(&Vector2::Sum), 5);
}