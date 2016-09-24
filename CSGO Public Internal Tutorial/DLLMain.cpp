#include "SDK.hpp"
//our paint traverse hook  could define it elsewhere if you want since it's declared in sdk.hpp....
void __stdcall hkPaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	//function....
	typedef void(__stdcall* PaintTraverse_t)(unsigned int, bool, bool);
	SDK::Hooks.PanelVMT->Function<PaintTraverse_t>(41)(vguiPanel, forceRepaint, allowForce);
	//grabbing panel name...
	std::string szPanelName = SDK::Interfaces.Panel->GetName(vguiPanel);
	//panel which is ontop.
	if (!szPanelName.empty() && !szPanelName.compare("FocusOverlayPanel"))
	{
		static bool startdraw = true;
		if (startdraw)
		{
			SDK::Draw.Start();
			startdraw = false;
		}

		SDK::Draw.String(SDK::Draw.DefaultFont,10,10,Color(255,255,255,255),"Drawing Test!");
	}
}
//starting up the cheat
void Init()
{
	SDK::Utils.InitConsole("D9 Public Internal Example");
	//Grabbing interfaces
	printf("Grabbing Interfaces : \n");
	SDK::Interfaces.Surface = SDK::Utils.FindInterface<ISurface*>("vguimatsurface.dll", "VGUI_Surface");
	SDK::Interfaces.Panel = SDK::Utils.FindInterface<IPanel*>("vgui2.dll", "VGUI_Panel");
	
	//grabbing panel
	DWORD dwPanelVMT = (DWORD)SDK::Interfaces.Panel;
	SDK::Hooks.PanelVMT = new cVMTHook(&dwPanelVMT);

	//hooking paint taverse -> 41
	SDK::Hooks.PanelVMT->Hook((DWORD)hkPaintTraverse, 41);
	printf("Hooked PaintTraverse!\n");

	// exit on key
	for (;;)
	{
		if (GetAsyncKeyState(VK_DELETE) && GetForegroundWindow() == FindWindowA("Valve001", NULL))
		{
			while (GetAsyncKeyState(VK_DELETE))
				Sleep(10);

			Beep(500, 500);
			//undoing hooks
			SDK::Hooks.PanelVMT->Undohook(41);
			//freeing console -> can then close it....
			FreeConsole();
		}
		Sleep(10);
	}
}
//dllmain
DWORD WINAPI DllMain(HMODULE hModule , DWORD dwReason, LPVOID lpvReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Init, NULL, NULL, NULL);
			break;
		case DLL_PROCESS_DETACH:
			break;
	}
	return 1;
}