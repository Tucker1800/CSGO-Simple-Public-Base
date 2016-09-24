#include "SDK.hpp"

void ISurface::DrawSetTextFont(unsigned long font)
{
		typedef void(__thiscall* origfn)(void*, unsigned long);
		SDK::Utils.GetVFunc<origfn>(this, 23)(this, font);
}

void ISurface::DrawSetTextColor(int r, int g, int b, int a)
{
	typedef void(__thiscall* origfn)(void*, Color);
	SDK::Utils.GetVFunc<origfn>(this, 25)(this, Color(r, g, b, a));
}

void ISurface::DrawSetTextPos(int x, int y)
{
	typedef void(__thiscall* origfn)(void*, int, int);
	SDK::Utils.GetVFunc<origfn>(this, 26)(this, x, y);
}

void ISurface::DrawPrintText(const wchar_t* wszText, int length)
{
	typedef void(__thiscall* origfn)(void*, const wchar_t*, int, int);
	SDK::Utils.GetVFunc<origfn>(this, 28)(this, wszText, length, 0);
}

unsigned long ISurface::CreateCSFont(void)
{
	typedef unsigned long(__thiscall* origfn)(void*);
	return SDK::Utils.GetVFunc<origfn>(this, 71)(this);
}

bool ISurface::SetFontGlyphSet(unsigned long font, const char* szName, int tall, int weight, int blur, int scanlines, FontFlags_t flags)
{
	typedef bool(__thiscall* origfn)(void*, unsigned long, const char*, int, int, int, int, FontFlags_t, int, int);
	return SDK::Utils.GetVFunc<origfn>(this, 72)(this, font, szName, tall, weight, blur, scanlines, flags, 0, 0);
}