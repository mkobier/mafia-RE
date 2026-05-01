#include "../../Core/memory.h"
#include "Tram.h"


void Tram::DecreaseActivePassengers()
{
    if (this->passengerActiveCount > 0)  
        --this->passengerActiveCount;
}

void Tram::InitHooks(uintptr_t gameBaseAddress)
{
    Memory::InstallHook(gameBaseAddress + ADDR_DECREASE_ACTIVE_PASSENGERS, FindFunctionAdress(&Tram::DecreaseActivePassengers), 5);
}