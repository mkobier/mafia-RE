#include "../../Core/memory.h"
#include "Tram.h"


void Tram::DecreaseActivePassengers()
{
    int currentActivePassengerCount = this->passengerActiveCount;
    if (currentActivePassengerCount)
        this->passengerActiveCount = currentActivePassengerCount - 1;
}

void Tram::InitHooks(uintptr_t gameBaseAddress)
{
    Memory::InstallHook(gameBaseAddress + ADDR_DECREASE_ACTIVE_PASSENGERS, FindFunctionAdress(&Tram::DecreaseActivePassengers), 5);
}