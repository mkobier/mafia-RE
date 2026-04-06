#include "TramPassenger.h"
#include "../../Core/memory.h"
#include <iostream>

TramPassenger* TramPassenger::CreateEmpty()
{
    this->fear_timer = 0;
    this->max_fear_time = 0;
    this->old_passenger_flag = 18;
    this->collision_data = nullptr;

    return this;
}

void TramPassenger::InitHooks(uintptr_t gameBaseAddress)
{
    Memory::InstallHook(gameBaseAddress + ADDR_CREATE_EMPTY,FindFunctionAdress(&TramPassenger::CreateEmpty), 5);
}