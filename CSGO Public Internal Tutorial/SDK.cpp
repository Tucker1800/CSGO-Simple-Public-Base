#include "SDK.hpp"
//declaring....
namespace SDK
{
	Utilities Utils;
	cHooks Hooks;
	cInterfaces Interfaces;
	cDraw Draw;
}
//starting up our draw class (creating our fonts) -> if you want to be able to resize csgo you need to restart this class to fix font fyi so a simple check....
void cDraw::Start()
{
	DefaultFont = SDK::Interfaces.Surface->CreateCSFont();
	SDK::Interfaces.Surface->SetFontGlyphSet(DefaultFont, "Impact", 20, 100, 0, 0, FONTFLAG_ANTIALIAS);
}
//simple string function
void cDraw::String(unsigned long font, int x, int y, Color color, const char* msg, ...)
{
	va_list va_alist;
	char buf[1024];
	va_start(va_alist, msg);
	_vsnprintf(buf, sizeof(buf), msg, va_alist);
	va_end(va_alist);
	wchar_t wbuf[1024];
	MultiByteToWideChar(CP_UTF8, 0, buf, 256, wbuf, 256);

	SDK::Interfaces.Surface->DrawSetTextFont(font);
	SDK::Interfaces.Surface->DrawSetTextColor(color.r(),color.g(),color.b(),color.a());
	SDK::Interfaces.Surface->DrawSetTextPos(x, y);
	SDK::Interfaces.Surface->DrawPrintText(wbuf, wcslen(wbuf));
}
