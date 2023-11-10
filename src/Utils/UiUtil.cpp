#ifndef INTTEMPLATE_UIUTIL_CPP
#define INTTEMPLATE_UIUTIL_CPP

#include "Utils/UiUtil.h"

#include <Windows.h>
#include <iostream>


bool ClearConsole()
{
	COORD CursorPosition;
	CursorPosition.X = 0;
	CursorPosition.Y = 0;
	if (SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition) != 0)
		return true;

	return false;
}

bool SetupConsole()
{
	// Wipe Screen Fully
	std::cout.clear();
	std::cin.clear();

	// Begin Console Setup
	HWND CurrentConsole = GetConsoleWindow();
	HANDLE StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	RECT ConsoleRect;
	CONSOLE_CURSOR_INFO CursorInfo;
	CONSOLE_FONT_INFOEX ConsoleFontInfo;

	// Setup Console Size
	if (GetWindowRect(CurrentConsole, &ConsoleRect) == 0)
		return false;

	if (MoveWindow(CurrentConsole, ConsoleRect.left, ConsoleRect.top, 800, 600, TRUE) == 0)
		return false;

	// Modify Font
	ConsoleFontInfo.cbSize = sizeof(ConsoleFontInfo);
	ConsoleFontInfo.dwFontSize.X = 0;
	ConsoleFontInfo.dwFontSize.Y = 24;
	ConsoleFontInfo.FontWeight = FW_BOLD;

	if (SetCurrentConsoleFontEx(StdHandle, FALSE, &ConsoleFontInfo) == 0)
		return false;

	// Hide Cursor
	if (GetConsoleCursorInfo(StdHandle, &CursorInfo) == 0)
		return false;

	CursorInfo.bVisible = false;

	if (SetConsoleCursorInfo(StdHandle, &CursorInfo) == 0)
		return false;
	return true;
}


#endif //INTTEMPLATE_UIUTIL_CPP