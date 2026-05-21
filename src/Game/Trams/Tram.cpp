#include "../../Core/memory.h"
#include "Tram.h"
#include <cstring>
#include <cmath>

typedef void(__thiscall* I3DFrame_UpdateWMatrixFunc)(I3DFrameModel* a1);
typedef Vector3*(__stdcall* Vector3_OperatorMulFunc)(Vector3* a1, Matrix4* a2);

static I3DFrame_UpdateWMatrixFunc g_I3DFrame_UpdateWMatrixProc = nullptr;
static Vector3_OperatorMulFunc g_Vector3_OperatorMul = nullptr;

static constexpr uintptr_t ADDR_UPDATE_W_MATRIX_PROC = 0x20FC30;
static constexpr uintptr_t ADDR_OPERATOR_MUL = 0x20FC54;

void Tram::UpdateOscillation(int deltaTimeMs, int carId, Vector3* carCenter, Vector3* directionVector, Vector3 frontPosition, Vector3 rearPosition)
{
    constexpr float EPSILON_SPEED = 0.00000001f;
    constexpr float EPSILON_LENGTH = 0.00000001f;
    constexpr float EPSILON_NORMALIZATION = 0.00000001f;
    constexpr float TWO_PI = 6.2831855f;           // 2*PI
    constexpr float HALF_PI = 1.5707964f;           // PI/2
    constexpr float BASE_AMPLITUDE = 0.03f;

    // If speed is close to zero - don't update sway physics
    if (this->actualSpeed < EPSILON_SPEED)
        return;

    // 1. Get 3D model
    I3DFrameModel* frameModel = nullptr;
    if (carId != 0)
    {
        frameModel = this->modelsBase[carId - 1];
    }
    else
    {
        frameModel = this->frameModel;
    }

    // 2. Ensure world matrix is updated
    constexpr unsigned int REQUIRED_FLAG = 0x20;
    if ((frameModel->stateFlags & REQUIRED_FLAG) == 0)
    {
        g_I3DFrame_UpdateWMatrixProc(frameModel);
    }

    // 3. Speed ratio (0.0 .. 1.0+)
    const float speedRatio = this->actualSpeed / this->maxSpeed;

    // 4. Prepare rotation matrix (without translation)
    Matrix4 rotationMatrix;
    std::memcpy(&rotationMatrix, &frameModel->globalMatrix, sizeof(rotationMatrix));
    std::memset(&rotationMatrix.pos, 0, sizeof(rotationMatrix.pos));

    // 5. Update oscillation phase
    const float deltaPhase = (static_cast<float>(deltaTimeMs) * speedRatio * 12.0f) / 1000.0f;

    float& carPhase = this->carOscillationArray[carId];
    carPhase += deltaPhase;

    // Wrap phase to range [0, 2*PI).
    if (carPhase > TWO_PI)
    {
        carPhase -= TWO_PI;
    }

    // 6. Determine pure direction vector (front) of vehicle
    Vector3 frontVector;
    frontVector.x = 1.0f;
    frontVector.z = 0.0f;
    frontVector.y = 0.0f;
    g_Vector3_OperatorMul(&frontVector, &rotationMatrix);

    // 7. Calculate sway offset vector
    const float phaseCos = std::sin(carPhase + HALF_PI);

    const float offsetX = frontVector.x * phaseCos;
    const float offsetZ = frontVector.z * phaseCos;
    const float offsetY = frontVector.y * phaseCos;

    // 8. Scale sway amplitude by speed
    Vector3 swayOffset;
    swayOffset.x = offsetX * BASE_AMPLITUDE * speedRatio;
    swayOffset.z = offsetZ * BASE_AMPLITUDE * speedRatio;
    swayOffset.y = offsetY * BASE_AMPLITUDE * speedRatio;

    // 9. Apply offset to couplers
    frontPosition.x += swayOffset.x;
    frontPosition.z += swayOffset.z;
    frontPosition.y += swayOffset.y;

    rearPosition.x -= swayOffset.x;
    rearPosition.z -= swayOffset.z;
    rearPosition.y -= swayOffset.y;

    // 10. Calculate direction vector (rear -> front)
    Vector3 rearToFrontVector;
    rearToFrontVector.CopyCoordinates(frontPosition.x - rearPosition.x, frontPosition.z - rearPosition.z, frontPosition.y - rearPosition.y);

    // Save direction vector before normalization
    directionVector->x = rearToFrontVector.x;
    directionVector->z = rearToFrontVector.z;
    directionVector->y = rearToFrontVector.y;

    // 11. Calculate car center
    Vector3 halfVector;
    halfVector.CopyCoordinates(rearToFrontVector.x * 0.5f, rearToFrontVector.z * 0.5f, rearToFrontVector.y * 0.5f);

    // center = rearPosition + halfVector
    Vector3 tempCenter;
    rearPosition.Addition(&tempCenter, &halfVector);

    *carCenter = tempCenter;

    // 12. DIRECTION VECTOR NORMALIZATION
    const float lengthSquared =
        directionVector->x * directionVector->x +
        directionVector->z * directionVector->z +
        directionVector->y * directionVector->y;

    if (std::fabs(lengthSquared - 1.0f) >= EPSILON_NORMALIZATION)
    {
        if (lengthSquared >= EPSILON_LENGTH)
        {
            const float inverseLength = 1.0f / std::sqrt(lengthSquared);
            directionVector->x *= inverseLength;
            directionVector->z *= inverseLength;
            directionVector->y *= inverseLength;
        }
        else
        {
            if (directionVector->x == 0.0f)
            {
                if (directionVector->y == 0.0f)
                {
                    if (directionVector->z >= 0.0f)
                        directionVector->z = 1.0f;
                    else
                        directionVector->z = -1.0f;
                }
                else if (directionVector->y >= 0.0f)
                {
                    directionVector->y = 1.0f;
                }
                else
                {
                    directionVector->y = -1.0f;
                }
            }
            else if (directionVector->x >= 0.0f)
            {
                directionVector->x = 1.0f;
            }
            else
            {
                directionVector->x = -1.0f;
            }
        }
    }
}

void Tram::IncreaseActivePassengers()
{
    ++this->passengerActiveCount;
}

void Tram::DecreaseActivePassengers()
{
    if (this->passengerActiveCount > 0)  
        --this->passengerActiveCount;
}

void Tram::InitHooks(uintptr_t gameBaseAddress)
{
    g_I3DFrame_UpdateWMatrixProc = (I3DFrame_UpdateWMatrixFunc)(gameBaseAddress + ADDR_UPDATE_W_MATRIX_PROC);
    g_Vector3_OperatorMul = (Vector3_OperatorMulFunc)(gameBaseAddress + ADDR_OPERATOR_MUL);

    Memory::InstallHook(gameBaseAddress + ADDR_UPDATE_OSCILLATION, FindFunctionAdress(&Tram::UpdateOscillation), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_INCREASE_ACTIVE_PASSENGERS, FindFunctionAdress(&Tram::IncreaseActivePassengers), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_DECREASE_ACTIVE_PASSENGERS, FindFunctionAdress(&Tram::DecreaseActivePassengers), 5);
}