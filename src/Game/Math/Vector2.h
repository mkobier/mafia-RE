#pragma once
#include <cstdint>

class Vector2
{
public:
    float x;
    float y;

    double __fastcall AngleBetweenVectors(Vector2* other);
    Vector2* Add(Vector2* other);
    Vector2* Multiply(Vector2* result, Vector2* operand);
    Vector2* Sum(Vector2* result, Vector2* addition);

    static void InitHooks(uintptr_t gameBaseAddress);

private:

    static constexpr uintptr_t ADDR_ANGLE_BETWEEN_VECTORS = 0x8490;
    static constexpr uintptr_t ADDR_VECTOR_ADD = 0x9B7C0;
    static constexpr uintptr_t ADDR_VECTOR_MULTIPLY = 0x1F7640;
    static constexpr uintptr_t ADDR_VECTOR_SUM = 0x1F7660;
};