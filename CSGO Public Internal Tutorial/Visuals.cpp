#include "SDK.hpp"
#include "Visuals.hpp"

void cVisuals::Start()
{
	SDK::Draw.String(SDK::Draw.DefaultFont, 10, 10, Color(255, 255, 255, 255), "Drawing Test!");
}