#include <MainHackThread.h>

#include "Utils/Directx9Utils.h"

#include "Utils/MemUtil.h"

#include <sstream>
#include <Utils/GameUtils.h>

void DrawUtils::DrawLineF(int x1, int y1, int x2, int y2, int Thickness, D3DCOLOR Color)
{
	if (!LineL)
		D3DXCreateLine(D9Utils.pDevice, &LineL);

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
	if (!FontF)
		D3DXCreateFont(D9Utils.pDevice, 18, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
			CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &FontF);

	RECT Rect;

	SetRect(&Rect, x, y, x, y);

	FontF->DrawText(NULL, Text, -1, &Rect, DT_CENTER | DT_NOCLIP, Color);
}

void DrawUtils::DrawMenu()
{
	int MenuOffx = D9Utils.WindowWidth / 2;
	int MenuOffy = 10;

	D3DCOLOR Enabled = D3DCOLOR_ARGB(255, 0, 255, 0);
	D3DCOLOR Disabled = D3DCOLOR_ARGB(255, 255, 0, 0);


	if (!HThread.THack.T_Menu)
		DrawTextF("Show Menu [F1]", MenuOffx, MenuOffy, D3DCOLOR_ARGB(255, 255, 255, 255));
	else
	{
		DrawTextF("Stat Hack [F10]", MenuOffx, MenuOffy + 0 * 18, HThread.THack.T_Stats ? Enabled : Disabled);
		DrawTextF("Teleport Entity to Blink Hack [F9]", MenuOffx, MenuOffy + 1 * 18,
			HThread.THack.T_BlinkReady ? Enabled : Disabled);
		DrawTextF("Power Hack [F8]", MenuOffx, MenuOffy + 2 * 18, HThread.THack.T_PowerTimer ? Enabled : Disabled);
		DrawTextF("Player Detection Hack [F7]", MenuOffx, MenuOffy + 3 * 18,
			HThread.THack.T_PlayerDetection ? Enabled : Disabled);
		DrawTextF("Add Runes Instead of Decreasing [F6]", MenuOffx, MenuOffy + 4 * 18,
			HThread.THack.T_Runes ? Enabled : Disabled);
		DrawTextF("Max Blink Hack [F5]", MenuOffx, MenuOffy + 5 * 18, HThread.THack.T_BlinkReady ? Enabled : Disabled);
	}
}

void DrawUtils::DrawESP()
{
	uintptr_t EntityListAddress = Mem::FindDMAAddy(HThread.ModuleBase + GOffset.EntList, { 0x48, 0x280, 0x0 });


	float Matrix[9];
	memcpy(&Matrix, (PBYTE)(HThread.ModuleBase + 0x1072F10), sizeof(Matrix));

	for (unsigned int i = 0; i < 64; i++)
	{
		PlayerObject* Entity = *(PlayerObject**)(EntityListAddress + i * 0x04);

		if (ValidateEntity(Entity))
		{
			Vec2 EntPos;

			D3DCOLOR Color = D3DCOLOR_ARGB(255, 255, 0, 0);

			if (W2Screen(Matrix, Entity->BodyPos3, EntPos))
			{
				DrawLineF(EntPos.x, EntPos.y, D9Utils.WindowWidth / 2, D9Utils.WindowHeight - 20, 2, Color);
			}
		}
	}
}
