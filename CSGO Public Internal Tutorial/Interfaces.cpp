#include "SDK.hpp"

void cInterfaces::Start()
{
	SDK::Interfaces.Surface = SDK::Utils.FindInterface<ISurface*>("vguimatsurface.dll", "VGUI_Surface");
	SDK::Interfaces.Panel = SDK::Utils.FindInterface<IPanel*>("vgui2.dll", "VGUI_Panel");
}