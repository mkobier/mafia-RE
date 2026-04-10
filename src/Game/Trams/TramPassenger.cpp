#include "../../Core/memory.h"
#include "TramPassenger.h"
#include "../Math/Math.h"
#include <iostream>

typedef void(__thiscall* SendAnimToEngineFunc)(TramPassenger* pThis, unsigned int a2);

static SendAnimToEngineFunc g_SendAnimationToEngine = nullptr;

static constexpr uintptr_t ADDR_SEND_ANIM = 0x841A0;

TramPassenger* TramPassenger::CreateEmpty()
{
    this->fear_timer = 0;
    this->max_fear_time = 0;
    this->old_passenger_flag = 18;
    this->collision_data = nullptr;

    return this;
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

void TramPassenger::InitHooks(uintptr_t gameBaseAddress)
{
    g_SendAnimationToEngine = (SendAnimToEngineFunc)(gameBaseAddress + ADDR_SEND_ANIM);

    Memory::InstallHook(gameBaseAddress + ADDR_CREATE_EMPTY,FindFunctionAdress(&TramPassenger::CreateEmpty), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_CREATE_FEAR, FindFunctionAdress(&TramPassenger::CreateFear), 5);

}