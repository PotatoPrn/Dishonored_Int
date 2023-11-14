#ifndef INTTEMPLATE_HACKLIST_CPP
#define INTTEMPLATE_HACKLIST_CPP

#define TOGGLE(x) x = !x
#define DISPLAY(x, y) std::cout << #x << (y ? " O" : " X") << "\n"

#include "MainHackThread.h"

#include "Utils/UiUtil.h"
#include "Utils/MemUtil.h"

#include "Utils/Directx9Utils.h"


#include <iostream>

HackThread HThread;
GameOffset GOffset;
DX9Utils D9Utils;
DrawUtils DUtils;


void HackThread::Init()
{
	const char* ModuleName = "Dishonored.exe";

	do
	{
		HThread.ModuleBase = (uintptr_t)GetModuleHandleA(ModuleName);
	}
	while (HThread.ModuleBase == NULL);

	// Probs setup Directx stuff if needed in the future
}


void HackThread::MainHackThread()
{
	HThread.Init();

	PlayerEnt = *(PlayerObject**)(ModuleBase + GOffset.PlayerEnt);

	// SingleLine Offset :/
	BStat = (BlinkClass*)(*(uintptr_t*)(ModuleBase + GOffset.F_BlinkBase) + 0x170);

	if (BStat != nullptr && BStat->BlinkInfo != nullptr)
		THack.T_BlinkReady = true;
	else
		THack.T_BlinkReady = false;


	if (GetAsyncKeyState(VK_F10) & 1)
		TOGGLE(THack.T_Stats);

	if (GetAsyncKeyState(VK_F9) & 1)
		HFunction.H_TPEnt();

	if (GetAsyncKeyState(VK_F8) & 1)
		TOGGLE(THack.T_PowerTimer);

	if (GetAsyncKeyState(VK_F7) & 1)
		TOGGLE(THack.T_PlayerDetection);

	if (GetAsyncKeyState(VK_F6) & 1)
		TOGGLE(THack.T_Runes);

	if (GetAsyncKeyState(VK_F5) & 1 && THack.T_BlinkReady)
	{
		BStat->BlinkInfo->Distance = 9999; // Crashes when player dies, will need to validate player Status
		BStat->BlinkInfo->Height = 9999;
	}

	if (GetAsyncKeyState(VK_F1) & 1)
		TOGGLE(THack.T_Menu);

	/// Enabled Hacks

	if (THack.T_Stats)
	{
		HFunction.H_Stats();
		HFunction.H_Ammo();
	}

	if (THack.T_PowerTimer)
	{
		// Disable Possession Usage Timer
		Mem::PatchNop((BYTE*)(ModuleBase + GOffset.F_PossessionTimer), 8);

		// Disable DarkVision Usage Timer
		Mem::PatchNop((BYTE*)(ModuleBase + GOffset.F_DarkEyeTimer), 8);
	}
	else
	{
		// Enable Possession Timer
		// movss [esi+00000094],xmm0
		Mem::PatchByte((BYTE*)(ModuleBase + GOffset.F_PossessionTimer),
			(BYTE*)"\xF3\x0F\x11\x86\x94\x00\x00\x00", 8);

		// Enable Dark Vision Timer
		// movss [ebx+00000094],xmm0
		Mem::PatchByte((BYTE*)(ModuleBase + GOffset.F_DarkEyeTimer),
			(BYTE*)"\xF3\x0F\x11\x83\x94\x00\x00\x00", 8);
	}

	if (THack.T_PlayerDetection)
		// Disable Power Detection
		Mem::PatchNop((BYTE*)(ModuleBase + GOffset.F_PlayerDetection), 6);
	else
		// Enable Player Detection
		// mov [esi+000000AC],bl
		Mem::PatchByte((BYTE*)(ModuleBase + GOffset.F_PlayerDetection),
			(BYTE*)"\x88\x9E\xAC\x00\x00\x00", 6);

	if (THack.T_Runes)
		Mem::PatchByte((BYTE*)(ModuleBase + GOffset.F_Runes), (BYTE*)"\x01\xFA",
			2); // add EDX, EDI
	else
		Mem::PatchByte((BYTE*)(ModuleBase + GOffset.F_Runes), (BYTE*)"\x2B\xD7",
			2); // sub EDX, EDI


	/// Display Functions
	bool DisplayHK = true;
	if (DisplayHK)
	{
		DISPLAY(DEL Exit Hack, true);
		DISPLAY(F10 Infinite Stats, THack.T_Stats);
		DISPLAY(F9 Ent Hack, THack.T_EntHack);
		DISPLAY(F8 Infinite Power, THack.T_PowerTimer);
		DISPLAY(F7 Disable Player Detection, THack.T_PlayerDetection);
		DISPLAY(F6 Enable Rune Hack, THack.T_Runes);
		DISPLAY(F5 Modify BlinkDistance, THack.T_Teleport);
	}

	ClearConsole();
}


#endif //INTTEMPLATE_HACKLIST_CPP
