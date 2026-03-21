#include "Vector2.h"
#include "../../Core/Memory.h"
#include <iostream>

Vector2* Vector2::Add(Vector2* other)
{
    this->x += other->x;
    this->y += other->y;

    return this;
}

Vector2* Vector2::Multiply(Vector2* result, Vector2* operand)
{
    result->x = operand->x * this->x;
    result->y = operand->y * this->y;

    return result;
}

Vector2* Vector2::Sum(Vector2* result, Vector2* addition)
{
    result->x = this->x + addition->x;
    result->y = this->y + addition->y;

    return result;
}

void Vector2::InitHooks(uintptr_t gameBaseAddress)
{
    Memory::InstallHook(gameBaseAddress + ADDR_VECTOR_ADD, FindFunctionAdress(&Vector2::Add), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_VECTOR_MULTIPLY, FindFunctionAdress(&Vector2::Multiply), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_VECTOR_SUM, FindFunctionAdress(&Vector2::Sum), 5);
}