#include "../../Core/memory.h"
#include "TramPassenger.h"
#include "../Math/Math.h"
#include <iostream>

typedef void(__thiscall* SendAnimToEngineFunc)(TramPassenger* pThis, unsigned int a2);
typedef void(__thiscall* DecreasePassengersFunc)(void* tram);

static SendAnimToEngineFunc g_SendAnimationToEngine = nullptr;
static DecreasePassengersFunc g_DecreasePassengers = nullptr;

static constexpr uintptr_t ADDR_SEND_ANIM = 0x841A0;
static constexpr uintptr_t ADDR_DECREASE_PASSENGERS = 0x97990;

TramPassenger* TramPassenger::CreateEmpty()
{
    this->fear_timer = 0;
    this->max_fear_time = 0;
    this->old_passenger_flag = 18;
    this->collision_data = nullptr;

    return this;
}

void TramPassenger::Kill(void* tram)
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
        g_DecreasePassengers(tram);
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

void TramPassenger::InitHooks(uintptr_t gameBaseAddress)
{
    g_SendAnimationToEngine = (SendAnimToEngineFunc)(gameBaseAddress + ADDR_SEND_ANIM);
    g_DecreasePassengers = (DecreasePassengersFunc)(gameBaseAddress + ADDR_DECREASE_PASSENGERS);


    Memory::InstallHook(gameBaseAddress + ADDR_CREATE_EMPTY,FindFunctionAdress(&TramPassenger::CreateEmpty), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_KILL, FindFunctionAdress(&TramPassenger::Kill), 5);
    Memory::InstallHook(gameBaseAddress + ADDR_CREATE_FEAR, FindFunctionAdress(&TramPassenger::CreateFear), 5);

}