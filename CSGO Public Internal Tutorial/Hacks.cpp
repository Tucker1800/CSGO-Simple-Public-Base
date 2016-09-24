#include "SDK.hpp"

void cHacks::Start()
{
	SDK::Utils.InitConsole("D9 Public Internal Example");

	//Grabbing interfaces
	printf("Grabbing Interfaces : \n");
	SDK::Interfaces.Start();

	//Hooks
	SDK::Hooks.Start();

	// exit on key
	for (;;)
	{
		if (GetAsyncKeyState(VK_DELETE) && GetForegroundWindow() == FindWindowA("Valve001", NULL))
		{
			while (GetAsyncKeyState(VK_DELETE))
				Sleep(10);

			Beep(500, 500);
			//undoing hooks
			SDK::Hooks.Exit();
			//freeing console -> can then close it....
			FreeConsole();
		}
		Sleep(10);
	}
}


void cHacks::StartVisuals()
{
	cVisuals Visuals;
	Visuals.Start();
}