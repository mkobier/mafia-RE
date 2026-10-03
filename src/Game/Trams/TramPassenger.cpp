#include "../../Core/memory.h"
#include "../../Core/GameThunks.h"
#include "../Math/Math.h"
#include "../Math/Vector3.h"
#include "../Math/Vector2.h"
#include "TramPassenger.h"
#include "Tram.h"
#include <iostream>
#include <cstring>

typedef void(__thiscall* RotateAndNormalizeFunc)(Vector3* pThis, float angle);
typedef void(__thiscall* SendAnimToEngineFunc)(TramPassenger* pThis, unsigned int a2);
typedef void(__cdecl* MakeStringPrintableFunc)(char* str);


static RotateAndNormalizeFunc g_RotateAndNormalizeVector = nullptr;
static SendAnimToEngineFunc g_SendAnimationToEngine = nullptr;
static MakeStringPrintableFunc g_MakeStringPrintable = nullptr;


static constexpr uintptr_t ROTATE_AND_NORMALIZE_VECTOR = 0x84D0;
static constexpr uintptr_t ADDR_SEND_ANIM = 0x841A0;
static constexpr uintptr_t ADDR_MAKE_PRINTABLE = 0x210ACC;


TramPassenger* TramPassenger::CreateEmpty()
{
    this->fear_timer = 0;
    this->max_fear_time = 0;
    this->old_passenger_flag = 18;
    this->collision_data = nullptr;

    return this;
}

void TramPassenger::Kill(Tram* tram)
{
    if (this->passenger_flag == 22)
        this->passenger_flag = this->old_passenger_flag;

    switch (this->passenger_flag)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
        tram->DecreaseActivePassengers();
        __fallthrough;
    case 6:
    case 7:
    case 8:
        this->new_animation_number = Math::Random(5) + 7;
        break;
    case 9:
    case 21:
        this->new_animation_number = Math::Random(2) + 12;
        break;
    case 19:
        this->new_animation_number = Math::Random(2) + 23;
        break;
    default:
        break;
    }

    this->passenger_flag = 17;
    g_SendAnimationToEngine(this, 1u);
}

bool TramPassenger::TurnTowardsTarget(Vector3 lookTarget, unsigned int deltaTime)
{
    typedef void(__stdcall* AssignPositionVectorFunc)(I3DFrameModel* pThis, Vector3* vec, float arg3);

    if (!this->frame_model)
        return false;

    I3DFrameModel* model = this->frame_model;

    bool matrixJustUpdated = false;

    // 1. Matrix update
    if (!(model->stateFlags & 0x10))
    {
        model->stateFlags |= 0x10;
        void* quat = (void*)&model->rotation;
        g_SQuatNormalize(quat);

        void* mat = (void*)&model->localMatrix;
        g_SMatrixSetRot3(mat, quat);

        matrixJustUpdated = true;
    }

    // 2. Extract direction vector from local matrix row 2 (offset 0x50 + 0x20 = 0x70)
    Vector3* row2 = (Vector3*)((uintptr_t)&model->localMatrix + 0x20);

    float dirX = row2->x;
    float dirY = row2->y;
    float dirZ = row2->z;

    // 3. Normalize the direction vector
    if (!matrixJustUpdated)
    {
        float lengthSq = (dirX * dirX) + (dirY * dirY) + (dirZ * dirZ);

        if (std::fabs(lengthSq - 1.0f) >= 1e-8f)
        {
            if (lengthSq >= 1e-8f)
            {
                float invLen = 1.0f / std::sqrt(lengthSq);
                dirX *= invLen;
                dirY *= invLen;
                dirZ *= invLen;
            }
            else
            {
                if (dirX != 0.0f)
                {
                    dirX = (dirX >= 0.0f) ? 1.0f : -1.0f;
                    dirY = 0.0f;
                    dirZ = 0.0f;
                }
                else if (dirY != 0.0f)
                {
                    dirY = (dirY >= 0.0f) ? 1.0f : -1.0f;
                    dirX = 0.0f;
                    dirZ = 0.0f;
                }
                else
                {
                    dirZ = (dirZ >= 0.0f) ? 1.0f : -1.0f;
                    dirX = 0.0f;
                    dirY = 0.0f;
                }
            }
        }
    }

    // 4. Project onto 2D plane
    Vector2 currentDir2D;
    currentDir2D.x = dirX;
    currentDir2D.y = dirY;

    Vector2 targetDir2D;
    targetDir2D.x = lookTarget.x;
    targetDir2D.y = lookTarget.y;

    // Calculate angle between vectors
    double angle = targetDir2D.AngleBetweenVectors(&currentDir2D);

    // 5. Determine animation ID and rotation speed
    int animId = (angle <= 0.0) ? 6 : 5;
    float speed = (angle <= 0.0) ? 2.0f : -2.0f;

    this->new_animation_number = animId;

    // Calculate max rotation step for the current frame (ms to seconds)
    float maxRotStep = static_cast<float>(deltaTime) * 0.001f * speed;

    // 6. Rotation logic
    if (std::fabs(angle) >= std::fabs(maxRotStep))
    {
        // Passenger is still turning
        Vector3 newDir;
        newDir.x = dirX;
        newDir.y = dirY;
        newDir.z = dirZ;

        g_RotateAndNormalizeVector(&newDir, maxRotStep);
        AssignPositionVectorFunc assignPos = (AssignPositionVectorFunc)model->vftable[3];
        assignPos(model, &newDir, 0.0f);

        return true;
    }
    else
    {
        // Passenger reached the target
        this->new_animation_number = 0;

        AssignPositionVectorFunc assignPos = (AssignPositionVectorFunc)model->vftable[3];
        assignPos(model, &lookTarget, 0.0f);

        return false;
    }
}

void TramPassenger::CreateFear(int new_max_fear_time)
{
    switch (this->passenger_flag)
    {
    case 6:
    case 7:
    case 8:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        this->old_passenger_flag = this->passenger_flag;
        this->passenger_flag = 22;
        this->new_animation_number = Math::Random(6) + 17;
        this->old_animation_number = this->animation_number;
        this->max_fear_time = new_max_fear_time;
        this->fear_timer = 0;
        g_SendAnimationToEngine(this, 1u);
        break;
    case 9:
        this->passenger_flag = 21;
        this->new_animation_number = Math::Random(2) + 15;
        this->max_fear_time = new_max_fear_time;
        this->fear_timer = 0;
        g_SendAnimationToEngine(this, 1u);
        break;
    default:
        return;
    }
}

bool TramPassenger::IsFemaleAnimation()
{
    typedef I3DFrameModel* (__stdcall* GetChildFrameFunc)(I3DFrameModel* pThis, const char* name, unsigned short index);

    if (!this->frame_model)
        return false;

    auto getChildFrame = (GetChildFrameFunc)(this->frame_model->vftable[14]);
    I3DFrameModel* backFrame = getChildFrame(this->frame_model, "back1", 0xFFFF);

    if (!backFrame)
        return false;

    const char* userProperties = backFrame->userProperties;
    if (!userProperties)
        userProperties = "";

    char buffer[64];
    strcpy(buffer, userProperties);

    if (strlen(buffer) <= 3)
        return false;

    g_MakeStringPrintable(buffer);

    return buffer[0] == 'B';
}

void TramPassenger::InitHooks(uintptr_t gameBaseAddress)
{
    g_SendAnimationToEngine = (SendAnimToEngineFunc)(gameBaseAddress + ADDR_SEND_ANIM);
    g_MakeStringPrintable = (MakeStringPrintableFunc)(gameBaseAddress + ADDR_MAKE_PRINTABLE);
    g_RotateAndNormalizeVector = (RotateAndNormalizeFunc)(gameBaseAddress + ROTATE_AND_NORMALIZE_VECTOR);

    Memory::InstallHook(gameBaseAddress + ADDR_CREATE_EMPTY,FindFunctionAdress(&TramPassenger::CreateEmpty), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_TURN_TOWARDS_TARGET, FindFunctionAdress(&TramPassenger::TurnTowardsTarget), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_KILL, FindFunctionAdress(&TramPassenger::Kill), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_CREATE_FEAR, FindFunctionAdress(&TramPassenger::CreateFear), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_IS_FEMALE_ANIM, FindFunctionAdress(&TramPassenger::IsFemaleAnimation), 5);
}