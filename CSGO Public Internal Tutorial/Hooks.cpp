#include "SDK.hpp"

void cHooks::Start()
{
	//grabbing panel
	DWORD dwPanelVMT = (DWORD)SDK::Interfaces.Panel;
	SDK::Hooks.PanelVMT = new cVMTHook(&dwPanelVMT);

	//hooking paint taverse -> 41
	SDK::Hooks.PanelVMT->Hook((DWORD)hkPaintTraverse, 41);
	printf("Hooked PaintTraverse!\n");
}

void cHooks::Exit()
{
	//unhooking
	SDK::Hooks.PanelVMT->Undohook(41);
}