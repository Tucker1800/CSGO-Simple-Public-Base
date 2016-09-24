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
		SDK::Hacks.StartVisuals();
	}
}
