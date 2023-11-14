#ifndef INTTEMPLATE_HACKLIST_H
#define INTTEMPLATE_HACKLIST_H

#include "Offsets.h"

#define PI 3.14159

/// HackThread Class
class HackThread
{
public:
	uintptr_t ModuleBase;
	PlayerObject* PlayerEnt;
	BlinkClass* BStat;

	void Init();

	void MainHackThread();

	struct ToggledHacks
	{
		bool T_Menu = false;

		bool T_Stats = false;

		bool T_AmmoHack = false;

		bool T_EntHack = false;

		bool T_PowerTimer = false;
		bool T_PlayerDetection = false;
		bool T_Runes = false;

		bool T_Teleport = false;

		bool T_BlinkReady = false;
	} THack;


	struct HackFunctions
	{
		void H_Stats();
		void H_Ammo();
		void H_TPEnt();

	} HFunction;
};

extern HackThread HThread;


#endif //INTTEMPLATE_HACKLIST_H
