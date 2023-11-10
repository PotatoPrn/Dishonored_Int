#ifndef INTTEMPLATE_MEMUTIL_CPP
#define INTTEMPLATE_MEMUTIL_CPP

#include "Utils/MemUtil.h"

char* BasicPatternScan(char* Base, size_t Size, char* Pattern, char* Mask)
{
	size_t PatternLen = strlen(Mask);

	for (unsigned int i = 0; i < Size; i++)
	{
		bool Found = true;

		for (unsigned int j = 0; j < PatternLen; j++)
		{
			if (Mask[j] != '?' && Pattern[j] != *(char*)((intptr_t)Base + i + j))
			{
				Found = false;
				break;
			}
		}
		if (Found)
		{
			return (Base + i);
		}
	}
	return nullptr;
}

char* InternalScanWrapper(char* Begin, size_t Size, char* Pattern, char* Mask)
{
	char* Match{ nullptr };

	DWORD OldProc = 0;

	MEMORY_BASIC_INFORMATION mbi{};

	for (char* curr = Begin; curr < Begin + Size; curr += mbi.RegionSize)
	{
		if (!VirtualQuery(curr, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS) continue;

		if (VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &OldProc))
		{
			Match = BasicPatternScan(curr, mbi.RegionSize, Pattern, Mask);

			VirtualProtect(mbi.BaseAddress, mbi.RegionSize, OldProc, &OldProc);

			if (Match != nullptr)
			{
				break;
			}
		}
	}
	return Match;
}


/// Main Mem Utils

uintptr_t Mem::FindDMAAddy(uintptr_t AddrPtr, std::vector<unsigned int> MultiLevelOffset)
{
	uintptr_t AddressValue = AddrPtr;

	for (unsigned int i = 0; i < MultiLevelOffset.size(); i++)
	{
		AddressValue = *(uintptr_t*)AddressValue;
		AddressValue += MultiLevelOffset[i];
	}
	return AddressValue;
}

uintptr_t Mem::PatternScanModule(char* Module, char* Pattern, char* Mask)
{
	MODULEINFO ModuleInfo = { 0 };
	HMODULE hModule;
	hModule = GetModuleHandle(Module);

	if (GetModuleInformation(GetCurrentProcess(), hModule, &ModuleInfo, sizeof(ModuleInfo)) == 0)
		return 0;

	char* Match = InternalScanWrapper((char*)ModuleInfo.lpBaseOfDll, ModuleInfo.SizeOfImage, Pattern, Mask);

	return (uintptr_t)Match;
}

void Mem::PatchByte(BYTE* Dst, BYTE* Src, unsigned int Size)
{
	DWORD oProc;

	VirtualProtect(Dst, Size, PAGE_EXECUTE_READWRITE, &oProc);
	memcpy(Dst, Src, Size);
	VirtualProtect(Dst, Size, oProc, &oProc);
}


#endif //INTTEMPLATE_MEMUTIL_CPP