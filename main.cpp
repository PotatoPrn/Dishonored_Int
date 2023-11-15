#include <Utils/MemUtil.h>
#ifndef INTTEMPLATE_MAIN_CPP
#define INTTEMPLATE_MAIN_CPP

#include "MainHackThread.h"

#include "Utils/Directx9Utils.h"

#include <Windows.h>
#include <iostream>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


void APIENTRY hkEndScene(LPDIRECT3DDEVICE9 o_pDevice)
{
	if (!D9Utils.pDevice)
		D9Utils.pDevice = o_pDevice;

	DUtils.DrawMenu();

	HThread.MainHackThread();

	D9Utils.oEndScene(D9Utils.pDevice);
}


/// Init Hack Thread
void InitHack(HMODULE hModule)
{
	if (D9Utils.Initd3d9(D9Utils.D3D9Device, sizeof(D9Utils.D3D9Device)))
	{
		memcpy(D9Utils.EndSceneBytes, (char*)D9Utils.D3D9Device[42], 7);

		D9Utils.oEndScene = (DX9Utils::tEndScene)Hook::Tramphook((char*)D9Utils.D3D9Device[42], (char*)hkEndScene, 7);
	}

	/// Key Bindings
	while (!GetAsyncKeyState(VK_DELETE))
		Sleep(1);


	Mem::PatchByte((BYTE*)D9Utils.D3D9Device[42], D9Utils.EndSceneBytes, 7);

	if (DUtils.FontF != NULL)
		DUtils.FontF->Release();

	if (DUtils.LineL != NULL)
		DUtils.LineL->Release();

	Sleep(1000);

	FreeLibraryAndExitThread(hModule, 0);
}

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


#endif //INTTEMPLATE_MAIN_CPP
