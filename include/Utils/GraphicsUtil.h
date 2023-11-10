#ifndef INTTEMPLATE_GRAPHICSUTIL_H
#define INTTEMPLATE_GRAPHICSUTIL_H

#include <Windows.h>

class ProcessUtils_T
{
public:
	int WindowWidth, WindowLength;
	HWND Window;

	static BOOL CALLBACK EnumWind(HWND Handle, LPARAM lp);

	HWND GetDeviceWindow();
};

extern ProcessUtils_T ProcessUtils;


#endif //INTTEMPLATE_GRAPHICSUTIL_H