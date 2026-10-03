#include "GameThunks.h"

I3DFrame_UpdateWMatrixFunc g_I3DFrame_UpdateWMatrixProc = nullptr;
Vector3_OperatorMulFunc g_Vector3_OperatorMul = nullptr;
SQuatNormalizeFunc g_SQuatNormalize = nullptr;
SMatrixSetRot3Func g_SMatrixSetRot3 = nullptr;

void InitThunks(uintptr_t gameBaseAddress)
{
    g_I3DFrame_UpdateWMatrixProc = (I3DFrame_UpdateWMatrixFunc)(gameBaseAddress + ADDR_UPDATE_W_MATRIX_PROC);
    g_Vector3_OperatorMul = (Vector3_OperatorMulFunc)(gameBaseAddress + ADDR_OPERATOR_MUL);
    g_SQuatNormalize = (SQuatNormalizeFunc)(gameBaseAddress + ADDR_SQUAT_NORMALIZE);
    g_SMatrixSetRot3 = (SMatrixSetRot3Func)(gameBaseAddress + ADDR_SMATRIX_SET_ROT3);
}