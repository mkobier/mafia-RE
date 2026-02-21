#pragma once
#include <cstdint>

class Vector3
{
public:
    float x;
    float z;
    float y;

    static constexpr uintptr_t ADDR_VECTOR_ADDITION = 0xAE00;
    static constexpr uintptr_t ADDR_VECTOR_ADDITION_SIMPLE = 0xBA00;
    static constexpr uintptr_t ADDR_VECTOR_SUBTRACTION = 0x7540;
    static constexpr uintptr_t ADDR_VECTOR_SUBTRACTION_SIMPLE = 0x564A0;
    static constexpr uintptr_t ADDR_VECTOR_SCALE = 0xADD0;
    static constexpr uintptr_t ADDR_VECTOR_SCALE_SIMPLE = 0xB9E0;
    static constexpr uintptr_t ADDR_VECTOR_DIVISION = 0x1CA370;
    static constexpr uintptr_t ADDR_VECTOR_DIVISION_SIMPLE = 0xF9BB0;
    static constexpr uintptr_t ADDR_VECTOR_SQUARED_LENGTH = 0x564D0;
    static constexpr uintptr_t ADDR_VECTOR_COPY_COORDINATES = 0x2A30;
    static constexpr uintptr_t ADDR_VECTOR_COPY = 0x38EE0;

    Vector3* Addition(Vector3* result, Vector3* addition);
    void AdditionSimple(Vector3* addition);
    Vector3* Subtraction(Vector3* result, Vector3* subtraction);
    Vector3* SubtractionSimple(Vector3* subtraction);
    Vector3* Scale(Vector3* result, float* scalar);
    void ScaleSimple(float* scalar);
    Vector3* Division(Vector3* result, float scalar);
    void DivisionSimple(float scalar);
    double SquaredLength();
    Vector3* CopyCoordinates(float x, float z, float y);
    Vector3* Copy(Vector3* dest);

    static void InitHooks(uintptr_t gameBaseAddress);
};