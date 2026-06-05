#include "GameThunks.h"

I3DFrame_UpdateWMatrixFunc g_I3DFrame_UpdateWMatrixProc = nullptr;
Vector3_OperatorMulFunc g_Vector3_OperatorMul = nullptr;

void InitThunks(uintptr_t gameBaseAddress)
{
    g_I3DFrame_UpdateWMatrixProc = (I3DFrame_UpdateWMatrixFunc)(gameBaseAddress + ADDR_UPDATE_W_MATRIX_PROC);
    g_Vector3_OperatorMul = (Vector3_OperatorMulFunc)(gameBaseAddress + ADDR_OPERATOR_MUL);
}