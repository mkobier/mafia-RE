#pragma once
#include <cstdint>

struct I3DFrameModel;
class Vector3;
class Matrix;

typedef void(__thiscall* I3DFrame_UpdateWMatrixFunc)(I3DFrameModel* a1);
typedef Vector3* (__stdcall* Vector3_OperatorMulFunc)(Vector3* a1, Matrix* a2);

extern I3DFrame_UpdateWMatrixFunc g_I3DFrame_UpdateWMatrixProc;
extern Vector3_OperatorMulFunc g_Vector3_OperatorMul;

constexpr uintptr_t ADDR_UPDATE_W_MATRIX_PROC = 0x20FC30;
constexpr uintptr_t ADDR_OPERATOR_MUL = 0x20FC54;

void InitThunks(uintptr_t gameBaseAddress);