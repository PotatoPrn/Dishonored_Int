#ifndef INTTEMPLATE_OFFSETS_H
#define INTTEMPLATE_OFFSETS_H

// Auto Padding
#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

#include "Utils/VectorUtil.h"

class PlayerObject
{
public:
	union
	{
		DEFINE_MEMBER_N(Vec3, ViewAngle1, 0x50); // Vec3
		DEFINE_MEMBER_N(Vec3, ViewAngle2, 0x60); // Vec3
		DEFINE_MEMBER_N(Vec3, BodyPos1, 0x80); // Vec3
		DEFINE_MEMBER_N(Vec3, BodyPos2, 0x90); // Vec3
		DEFINE_MEMBER_N(Vec3, BodyPos3, 0xC4); // Vec3 Modifiable
		DEFINE_MEMBER_N(Vec3, Acceleration1, 0x1B4); // Vec3
		DEFINE_MEMBER_N(Vec3, Acceleration2, 0x1C0); // Vec3
		DEFINE_MEMBER_N(Vec3, PHeadCoords1, 0x01F0); // Vec3
		DEFINE_MEMBER_N(int, Health, 0x344); // int
		DEFINE_MEMBER_N(Vec3, Acceleration3, 0x358); // Vec3
		DEFINE_MEMBER_N(Vec3, BodyPos4, 0x650); // Vec3
		DEFINE_MEMBER_N(Vec3, BodyPos5, 0x66C); // Vec3
		DEFINE_MEMBER_N(Vec3, BodyPos6, 0x7AC); // Vec3
		DEFINE_MEMBER_N(int, Mana, 0xA60); // int
		DEFINE_MEMBER_N(float, WaterBreathe, 0xAB8); // float
	};
};

class BlinkStat
{
public:
	union
	{
		DEFINE_MEMBER_N(float, Distance, 0x4);

		DEFINE_MEMBER_N(float, Height, 0x8);
	};
};

class BlinkClass
{
public:
	union
	{
		DEFINE_MEMBER_N(Vec3, BlinkPos, 0x60);

		DEFINE_MEMBER_N(PlayerObject*, PlayerEnt, 0x80);

		DEFINE_MEMBER_N(BlinkStat*, BlinkInfo, 0x128);
	};
};

class GameOffset
{
public:
	uintptr_t PlayerEnt = 0x105F628;
	uintptr_t EntList = 0x01049888;
	uintptr_t F_PossessionTimer = 0x7FB40B;
	uintptr_t F_DarkEyeTimer = 0x7F9B07;
	uintptr_t F_PlayerDetection = 0x75B752;
	uintptr_t F_Runes = 0x80F8F0;
	uintptr_t F_BlinkBase = 0x010719C4;
};

extern GameOffset GOffset;

#endif //INTTEMPLATE_OFFSETS_H
