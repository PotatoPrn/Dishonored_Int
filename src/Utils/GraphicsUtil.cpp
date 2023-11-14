#ifndef INTTEMPLATE_GRAPHICSUTILS_CPP
#define INTTEMPLATE_GRAPHICSUTILS_CPP

#include "Utils/GraphicsUtil.h"

ProcessUtils_T ProcessUtils;


BOOL CALLBACK ProcessUtils_T::EnumWind(HWND Handle, LPARAM lp)
{
	DWORD ProcID;

	GetWindowThreadProcessId(Handle, &ProcID);

	if (GetCurrentProcessId() != ProcID)
		return TRUE;

	if (Handle == GetConsoleWindow())
		return TRUE;

	return FALSE;
}

HWND ProcessUtils_T::GetDeviceWindow()
{
	ProcessUtils.Window = NULL;

	EnumWindows(ProcessUtils.EnumWind, NULL);

	RECT Size;
	GetWindowRect(ProcessUtils.Window, &Size);
	ProcessUtils.WindowWidth = Size.right - Size.left;
	ProcessUtils.WindowLength = Size.bottom - Size.top;

	return ProcessUtils.Window;
}


#endif //INTTEMPLATE_GRAPHICSUTILS_CPP
