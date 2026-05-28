#pragma once
#include "Vector3.h"

class Matrix
{
public:
    Vector3 row0;
    float element0_3;
    Vector3 row1;
    float element1_3;
    Vector3 row2;
    float element2_3;
    Vector3 pos;
    float element3_3;
};

static_assert(sizeof(Matrix) == 0x40, "Size of Matrix class is incorrect!");