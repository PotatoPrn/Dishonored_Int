#include "Utils/MemUtil.h"
#include "Utils/GameUtils.h"

#include "MainHackThread.h"


void HackThread::HackFunctions::H_Stats()
{
	HThread.PlayerEnt->Health = 70;
	HThread.PlayerEnt->Mana = 100;
	HThread.PlayerEnt->WaterBreathe = 30;
}


void HackThread::HackFunctions::H_Ammo()
{
	int NumberOfItems = 8;

	uintptr_t InventoryPtr = Mem::FindDMAAddy(HThread.ModuleBase + GOffset.PlayerEnt, { 0x59c, 0xBC, 0x0 });

	for (unsigned int i = 0; i < NumberOfItems; i++)
		*(int*)(InventoryPtr + i * 8) = 30;
}


void HackThread::HackFunctions::H_TPEnt()
{
	uintptr_t EntityListAddress = Mem::FindDMAAddy(HThread.ModuleBase + GOffset.EntList, { 0x48, 0x280, 0x0 });

	if (HThread.BStat != nullptr && HThread.BStat->BlinkInfo != nullptr && EntityListAddress != NULL)
	{
		for (unsigned int i = 0; i < 64; i++) // 128 is too big
		{
			PlayerObject* Entity = *(PlayerObject**)(EntityListAddress + i * 0x04);
			// Entitys from ENtlist dont use the same class as the player :/

			if (ValidateEntity(Entity) && Entity->Health != HThread.PlayerEnt->Health)
			{
				Entity->BodyPos3 = HThread.BStat->BlinkPos;
			}
		}
	}
	EntityListAddress = NULL;
}
