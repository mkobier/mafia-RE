#pragma once
#include <cstdint>

struct I3DFrameModel;
class Vector3;
class Matrix;

typedef void(__thiscall* I3DFrame_UpdateWMatrixFunc)(I3DFrameModel* a1);
typedef Vector3* (__stdcall* Vector3_OperatorMulFunc)(Vector3* a1, Matrix* a2);
typedef void(__stdcall* SQuatNormalizeFunc)(void* pThis);
typedef void(__stdcall* SMatrixSetRot3Func)(void* pThis, const void* quat);

extern I3DFrame_UpdateWMatrixFunc g_I3DFrame_UpdateWMatrixProc;
extern Vector3_OperatorMulFunc g_Vector3_OperatorMul;
extern SQuatNormalizeFunc g_SQuatNormalize;
extern SMatrixSetRot3Func g_SMatrixSetRot3;


constexpr uintptr_t ADDR_UPDATE_W_MATRIX_PROC = 0x20FC30;
constexpr uintptr_t ADDR_OPERATOR_MUL = 0x20FC54;
constexpr uintptr_t ADDR_SQUAT_NORMALIZE = 0x20FC3C;
constexpr uintptr_t ADDR_SMATRIX_SET_ROT3 = 0x20FC5A;

void InitThunks(uintptr_t gameBaseAddress);