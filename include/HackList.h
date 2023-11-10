#ifndef INTTEMPLATE_HACKLIST_H
#define INTTEMPLATE_HACKLIST_H

#include "Offsets.h"

#include <Windows.h>

#define PI 3.14159

/// HackThread Class
class HackThread_T
{
public:

	uintptr_t ModuleBase;
	PlayerObject* PlayerEnt;

	void Init();

	void MainHackThread();

	struct ToggledHacks
	{
		bool TestToggle = false;
	} THacks;


};

extern HackThread_T HackThread;


#endif //INTTEMPLATE_HACKLIST_H