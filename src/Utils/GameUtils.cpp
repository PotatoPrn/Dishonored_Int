#include "Utils/GameUtils.h"

#include <Utils/Directx9Utils.h>

bool ValidateEntity(PlayerObject* Entity)
{
	if (Entity == nullptr)
		return false;

	if (Entity->Health <= 0 || Entity->Health >= 300)
		return false;

	return true;
}


bool W2Screen(float Matrix[9], Vec3 Pos, Vec2& Screen)
{
	Vec3 ClipCoords;
	ClipCoords.x = Pos.x * Matrix[0] + Pos.y * Matrix[3] + Pos.z * Matrix[6];
	ClipCoords.y = Pos.x * Matrix[1] + Pos.y * Matrix[4] + Pos.z * Matrix[7];
	ClipCoords.z = Pos.x * Matrix[2] + Pos.y * Matrix[5] + Pos.z * Matrix[8];

	if (ClipCoords.z < 0.1f)
		return false;

	Vec2 NDC;
	NDC.x = ClipCoords.x / ClipCoords.z;
	NDC.y = ClipCoords.y / ClipCoords.z;

	Screen.x = (D9Utils.WindowWidth / 2 * NDC.x) + (NDC.x + D9Utils.WindowWidth / 2);
	Screen.y = -(D9Utils.WindowHeight / 2 * NDC.y) + (NDC.y + D9Utils.WindowHeight / 2);

	return true;
}
