#ifndef DIRECTX9UTILS_H
#define DIRECTX9UTILS_H

#include <d3d9.h>
#include <d3dx9.h>


#include <Windows.h>

#include "Utils/VectorUtil.h"

static HWND Window;

class DX9Utils
{
public:
	typedef HRESULT (APIENTRY*tEndScene)(LPDIRECT3DDEVICE9 pDevice);

	// Directx9 Variables
	LPDIRECT3DDEVICE9 pDevice = nullptr;
	void* D3D9Device[119];
	BYTE EndSceneBytes[7];
	tEndScene oEndScene = nullptr;


	// Window Handles
	int WindowWidth, WindowHeight;


	HWND GetDeviceWindow();

	bool Initd3d9(void** pTable, size_t Size);
};

extern DX9Utils D9Utils;


class DrawUtils
{
public:
	// Draw Variables
	ID3DXLine* LineL;
	ID3DXFont* FontF;

	void DrawLineF(int x1, int y1, int x2, int y2, int Thickness, D3DCOLOR Color);

	void DrawLineF(Vec2 Src, Vec2 Dst, int Thickness, D3DCOLOR Color);

	void DrawTextF(const char* Text, float x, float y, D3DCOLOR Color);

	void DrawMenu();

	void DrawESP();
};

extern DrawUtils DUtils;

#endif //DIRECTX9UTILS_H
