#include "../../Core/memory.h"
#include "../Math/Math.h"
#include "../Math/Vector3.h"
#include "TramPassenger.h"
#include "Tram.h"
#include <iostream>
#include <cstring>

typedef void(__thiscall* SendAnimToEngineFunc)(TramPassenger* pThis, unsigned int a2);
typedef void(__cdecl* MakeStringPrintableFunc)(char* str);

static SendAnimToEngineFunc g_SendAnimationToEngine = nullptr;
static MakeStringPrintableFunc g_MakeStringPrintable = nullptr;

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

    Memory::InstallHook(gameBaseAddress + ADDR_CREATE_EMPTY,FindFunctionAdress(&TramPassenger::CreateEmpty), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_KILL, FindFunctionAdress(&TramPassenger::Kill), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_CREATE_FEAR, FindFunctionAdress(&TramPassenger::CreateFear), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_IS_FEMALE_ANIM, FindFunctionAdress(&TramPassenger::IsFemaleAnimation), 5);
}