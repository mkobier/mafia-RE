#include "Vector3.h"
#include "../../Core/Memory.h"
#include <iostream>


Vector3* Vector3::Addition(Vector3* result, Vector3* addition)
{
    result->x = this->x + addition->x;
    result->z = this->z + addition->z;
    result->y = this->y + addition->y;

    return result;
}

void Vector3::AdditionSimple(Vector3* addition)
{
    this->x = this->x + addition->x;
    this->z = this->z + addition->z;
    this->y = this->y + addition->y;
}

Vector3* Vector3::Subtraction(Vector3* result, Vector3* subtraction)
{
    result->x = this->x - subtraction->x;
    result->y = this->y - subtraction->y;
    result->z = this->z - subtraction->z;

    return result;
}

Vector3* Vector3::SubtractionSimple(Vector3* subtraction)
{
    this->x = this->x - subtraction->x;
    this->z = this->z - subtraction->z;
    this->y = this->y - subtraction->y;

    return this;
}

Vector3* Vector3::Scale(Vector3* result, float* scalar)
{
    float s = *scalar;

    result->x = s * this->x;
    result->z = s * this->z;
    result->y = s * this->y;

    return result;
}

void Vector3::ScaleSimple(float* scalar)
{
    float s = *scalar;

    this->x = s * this->x;
    this->z = s * this->z;
    this->y = s * this->y;
}

Vector3* Vector3::Division(Vector3* result, float scalar)
{
    float inverse_scalar = 1.0f / scalar;

    result->x = inverse_scalar * this->x;
    result->z = inverse_scalar * this->z;
    result->y = inverse_scalar * this->y;

    return result;
}

void Vector3::DivisionSimple(float scalar)
{
    float inverse_scalar = 1.0f / scalar;

    this->x = inverse_scalar * this->x;
    this->z = inverse_scalar * this->z;
    this->y = inverse_scalar * this->y;
}

double Vector3::SquaredLength()
{
    return (double)(this->x * this->x) + (double)(this->z * this->z) + (double)(this->y * this->y);
}

Vector3* Vector3::CopyCoordinates(float x, float z, float y)
{
    this->x = x;
    this->z = z;
    this->y = y;

    return this;
}

Vector3* Vector3::Copy(Vector3* dest)
{
    dest->x = this->x;
    dest->z = this->z;
    dest->y = this->y;

    return dest;
}

void Vector3::InitHooks(uintptr_t gameBaseAddress) 
{
    Memory::InstallHook(gameBaseAddress + ADDR_VECTOR_ADDITION, FindFunctionAdress(&Vector3::Addition), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_VECTOR_ADDITION_SIMPLE, FindFunctionAdress(&Vector3::AdditionSimple), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_VECTOR_SUBTRACTION, FindFunctionAdress(&Vector3::Subtraction), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_VECTOR_SUBTRACTION_SIMPLE, FindFunctionAdress(&Vector3::SubtractionSimple), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_VECTOR_SCALE, FindFunctionAdress(&Vector3::Scale), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_VECTOR_SCALE_SIMPLE, FindFunctionAdress(&Vector3::ScaleSimple), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_VECTOR_DIVISION, FindFunctionAdress(&Vector3::Division), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_VECTOR_DIVISION_SIMPLE, FindFunctionAdress(&Vector3::DivisionSimple), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_VECTOR_SQUARED_LENGTH, FindFunctionAdress(&Vector3::SquaredLength), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_VECTOR_COPY_COORDINATES, FindFunctionAdress(&Vector3::CopyCoordinates), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_VECTOR_COPY, FindFunctionAdress(&Vector3::Copy), 5);
}