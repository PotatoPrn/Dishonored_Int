#include "Utils/Directx9Utils.h"

void DrawUtils::DrawLineF(int x1, int y1, int x2, int y2, int Thickness, D3DCOLOR Color)
{
Start:
	if (!LineL)
	{
		D3DXCreateLine(D9Utils.pDevice, &LineL);
		goto Start;
	}

	D3DXVECTOR2 Line[2];
	Line[0] = D3DXVECTOR2(x1, x2);
	Line[1] = D3DXVECTOR2(y1, y2);
	LineL->SetWidth(Thickness);
	LineL->Draw(Line, 2, Color);
}


void DrawUtils::DrawLineF(Vec2 Src, Vec2 Dst, int Thickness, D3DCOLOR Color)
{
	DrawLineF(Src.x, Src.y, Dst.x, Dst.y, Thickness, Color);
}


void DrawUtils::DrawTextF(const char* Text, float x, float y, D3DCOLOR Color)
{
Start:
	if (!FontF)
	{
		D3DXCreateFont(D9Utils.pDevice, 18, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
			CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &FontF);

		goto Start;
	}

	RECT Rect;

	SetRect(&Rect, x, y, x, y);

	FontF->DrawTextA(NULL, Text, -1, &Rect, DT_CENTER | DT_NOCLIP, Color);
}

void DrawUtils::DrawMenu()
{

}
