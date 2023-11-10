#ifndef INTTEMPLATE_HACKLIST_CPP
#define INTTEMPLATE_HACKLIST_CPP

#include "HackList.h"
#include "Utils/UiUtil.h"

#include <iostream>

HackThread_T HackThread;


void HackThread_T::Init()
{
	const char* ModuleName = "";

	do
	{
		HackThread.ModuleBase = (uintptr_t)GetModuleHandleA(ModuleName);
	} while (HackThread.ModuleBase == NULL);

	// Probs setup Directx stuff if needed in the future
}


void HackThread_T::MainHackThread()
{
	HackThread.Init();

	while (true)
	{

		if (GetAsyncKeyState(VK_DELETE) & 1)
			break;

		if (GetAsyncKeyState(VK_F10) & 1)
			THacks.TestToggle = !THacks.TestToggle;

		if (THacks.TestToggle)
			std::cout << std::hex << HackThread.ModuleBase << "\n";

		ClearConsole();
	}
}


#endif //INTTEMPLATE_HACKLIST_CPP