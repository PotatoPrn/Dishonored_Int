#ifndef INTTEMPLATE_MEMUTIL_H
#define INTTEMPLATE_MEMUTIL_H

#include <Windows.h>
#include <Psapi.h>

#include <vector>


namespace Mem
{
	uintptr_t FindDMAAddy(uintptr_t AddrPtr, std::vector<unsigned int> MultiLevelOffset);

	uintptr_t PatternScanModule(char* Module, char* Pattern, char* Mask);

	void PatchByte(BYTE* Dst, BYTE* Src, unsigned int Size);
}

char* BasicPatternScan(char* Base, size_t Size, char* Pattern, char* Mask);

char* InternalScanWrapper(char* Begin, size_t Size, char* Pattern, char* Mask);

#endif //INTTEMPLATE_MEMUTIL_H