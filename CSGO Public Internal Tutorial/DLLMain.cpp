#include "SDK.hpp"
//starting up the cheat
void Init()
{
	SDK::Hacks.Start();
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