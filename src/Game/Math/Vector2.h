#pragma once
#include <cstdint>

class Vector2
{
public:
    float x;
    float y;

    static constexpr uintptr_t ADDR_VECTOR_MULTIPLY = 0x1F7640;
    static constexpr uintptr_t ADDR_VECTOR_SUM = 0x1F7660;

    Vector2* Multiply(Vector2* result, Vector2* operand);
    Vector2* Sum(Vector2* result, Vector2* addition);

    static void InitHooks(uintptr_t gameBaseAddress);
};