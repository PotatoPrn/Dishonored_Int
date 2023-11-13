#include "Utils/Directx9Utils.h"

BOOL CALLBACK EnumWind(HWND Handle, LPARAM lp)
{
	DWORD ProcID;

	GetWindowThreadProcessId(Handle, &ProcID);

	if (GetCurrentProcessId() != ProcID)
		return false;

	if (Handle == GetConsoleWindow())
		return false;

	return true;
}


HWND DX9Utils::GetDeviceWindow()
{
	Window == NULL;

	EnumWindows(EnumWind, NULL);

	RECT Size;
	GetWindowRect(Window, &Size);

	WindowWidth = Size.right - Size.left;
	WindowHeight = Size.top - Size.bottom;

	return Window;
}

bool DX9Utils::Initd3d9(void** pTable, size_t Size)
{
	if (!pTable)
		return false;

	IDirect3D9* PD3D = Direct3DCreate9(D3D9b_SDK_VERSION);

	if (!PD3D)
		return false;

	IDirect3DDevice9* pDummyDevice = NULL;

	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.Windowed = false;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = GetDeviceWindow();

	HRESULT DummyDevCreated = PD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

	if (DummyDevCreated != S_OK)
	{
		d3dpp.Windowed = !d3dpp.Windowed;
		HRESULT DummyDevCreated = PD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

		if (DummyDevCreated != S_OK)
		{
			PD3D->Release();
			return false;
		}
	}

	memcpy(pTable, *(void***)(pDummyDevice), Size);

	pDummyDevice->Release();
	PD3D->Release();
	return true;
}
