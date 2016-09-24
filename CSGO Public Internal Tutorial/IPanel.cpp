#include "SDK.hpp"
const char* IPanel::GetName(unsigned int vguiPanel)
{
	typedef const char*(__thiscall* GetName_t)(void*, unsigned int);
	return SDK::Utils.GetVFunc<GetName_t>(this, 36)(this, vguiPanel);
}