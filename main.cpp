#ifndef INTTEMPLATE_MAIN_CPP
#define INTTEMPLATE_MAIN_CPP

#include "main.h"
#include "Utils/UiUtil.h"
#include "HackList.h"

#include <iostream>


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)InitHack, hModule, 0, nullptr));
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}



/// Init Hack Thread
void InitHack(HMODULE hModule)
{
	AllocConsole();
	FILE* fHandle;
	freopen_s(&fHandle, "CONOUT$", "w", stdout);

	if (ClearConsole() && SetupConsole())
	{
		HackThread.MainHackThread();
	}

	fclose(fHandle);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
}





#endif //INTTEMPLATE_MAIN_CPP