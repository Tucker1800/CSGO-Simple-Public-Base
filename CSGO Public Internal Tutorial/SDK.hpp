#include <Windows.h>
#include <string>
#include <iostream>

//declaring here for simplicity
class Utilities;
class cHooks;
class cInterfaces;
class cDraw;
//chucking them into a namespace to make usage easier.....
namespace SDK
{
	extern Utilities Utils;
	extern cHooks Hooks;
	extern cInterfaces Interfaces;
	extern cDraw Draw;
}
//utils class
class Utilities
{
public:
	//simple console starting so we can log stuff
	void InitConsole(std::string name)
	{
		AllocConsole();
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
		SetConsoleTitle(name.c_str());
	}
	//create interface function
	typedef void*(*CreateInterfaceFN)(const char* name, int* returncode);
	//find interfaces means no oudated shit, can't remember where this is from just ported it from one of my other projects.
	template<typename T>
	T FindInterface(std::string strModName, std::string strInterfaceName)
	{
		HMODULE mod = GetModuleHandleA(strModName.c_str());
		if (!mod)
			return nullptr;

		CreateInterfaceFN CreateInterfacefn = (CreateInterfaceFN)GetProcAddress(mod, "CreateInterface");
		if (!CreateInterfacefn)
			return nullptr;

		void* vInterface = nullptr;

		char* szInterface = new char[1024];

		for (int i = 0; i <= 999; i++)
		{
			sprintf(szInterface, "%s%03i", strInterfaceName.c_str(), i);
			vInterface = CreateInterfacefn(szInterface, NULL);

			if (vInterface)
			{
				printf("Found %s\n", szInterface);
				break;
			}
		}

		delete szInterface;

		if (vInterface == nullptr)
			printf("Didn't find %s\n", szInterface);

		return reinterpret_cast<T>(vInterface);
	}
	//template for finding vfuncs...
	template <typename T>
	T GetVFunc(void *vTabl, int i) 
	{
		return (*(T**)vTabl)[i];
	}
};
//simple vector struct should use a class once u want an aimbot etc...
struct Vector
{
	float x, y, z;
};
//simplified to what I needed for hooking but thanks to whoever posted the original class
class cVMTHook
{
public:
	cVMTHook(DWORD *inst)
	{
		dwInstance = (*(PDWORD**)inst);
		dwOldVMT = *dwInstance;
		VMTSize = VMTCount(dwOldVMT);

		if (VMTSize <= 0) 
			return;

		dwNewVMT = new DWORD[VMTSize];
		memcpy(dwNewVMT, dwOldVMT, sizeof(DWORD) * VMTSize);
		*dwInstance = (dwNewVMT);
		inst = dwNewVMT;
	}

	void Hook(DWORD dwNewFunc, unsigned int i)
	{
		if (dwNewVMT && dwOldVMT && i <= VMTSize && i >= 0)
		{
			dwNewVMT[i] = dwNewFunc;
		}
	}

	void Undohook(unsigned int i)
	{
		if (dwNewVMT && dwOldVMT && i <= VMTSize && i >= 0)
		{
			dwNewVMT[i] = dwOldVMT[i];
		}
	}

	template<typename T> T Function(int i)
	{
		return (T)(dwOldVMT[i]);
	}
private:
	DWORD VMTCount(PDWORD pdwVMT)
	{
		DWORD i;
		for (i = 0; pdwVMT[i]; i++)
		{
			if (IsBadCodePtr((FARPROC)pdwVMT[i]))
				break;
		}
		return i;
	}

	DWORD** dwInstance;
	DWORD*  dwNewVMT, *dwOldVMT;
	DWORD   VMTSize;
};
//hooks class to make it easy for people to copy the style and expand on this small base
class cHooks
{
public:
	cVMTHook* PanelVMT;
};
//ipanel.....
class IPanel
{
public:
	const char *GetName(unsigned int vguiPanel)
	{
		typedef const char*(__thiscall* GetName_t)(void*, unsigned int);
		return SDK::Utils.GetVFunc<GetName_t>(this, 36)(this, vguiPanel);
	}
};
//color class simplified from valve sdk......
class Color
{
private:
	int R, G, B, A;
public:
	Color() : R(0), G(0), B(0), A(0) {}
	Color(int r, int g, int b, int a) : R(r), G(g), B(b), A(a) {}
	Color(int r, int g, int b) : R(r), G(g), B(b), A(255) {}
	int r() { return R; }
	int g() { return G; }
	int b() { return B; }
	int a() { return A; }
	Color& operator = (Color& c)
	{
		R = c.r();
		G = c.g();
		B = c.b();
		A = c.a();
		return *this;
	}
};
//font flags
enum FontFlags_t
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
};
//isurface... Using color class to make life a bit easier i guess...
class ISurface
{
public:
	//setting font to use...
	void DrawSetTextFont(unsigned long HFont)
	{
		typedef void(__thiscall* origfn)(void*, unsigned long);
		SDK::Utils.GetVFunc<origfn>(this, 23)(this, HFont);
	}
	//homework is to use the function which uses Color class.... very close by :)
	void DrawSetTextColor(int r, int g, int b, int a)
	{
		typedef void(__thiscall* origfn)(void*, Color);
		SDK::Utils.GetVFunc<origfn>(this, 25)(this, Color(r, g, b, a));
	}
	//text pos
	void DrawSetTextPos(int x, int y)
	{
		typedef void(__thiscall* origfn)(void*, int, int);
		SDK::Utils.GetVFunc<origfn>(this, 26)(this, x, y);
	}
	//text itself
	void DrawPrintText(const wchar_t* wszText, int length, int drawfont = 0)
	{
		typedef void(__thiscall* origfn)(void*, const wchar_t*, int, int);
		SDK::Utils.GetVFunc<origfn>(this, 28)(this, wszText, length, drawfont);
	}
	//creating a new font
	unsigned long CreateCSFont(void)
	{
		typedef unsigned long(__thiscall* origfn)(void*);
		return SDK::Utils.GetVFunc<origfn>(this, 71)(this);
	}
	//font settings
	bool SetFontGlyphSet(unsigned long font, const char* szName, int tall, int weight, int blur, int scanlines, FontFlags_t flags, int nRangeMin = 0, int nRangeMax = 0)
	{
		typedef bool(__thiscall* origfn)(void*, unsigned long, const char*, int, int, int, int, FontFlags_t, int, int);
		return SDK::Utils.GetVFunc<origfn>(this, 72)(this, font, szName, tall, weight, blur, scanlines, flags, nRangeMin, nRangeMax);
	}
};
//interfaces class to keep it tidy.
class cInterfaces
{
public:
	ISurface* Surface;
	IPanel* Panel;
};
//simple draw class...
class cDraw
{
public:
	//defining fonts
	unsigned long DefaultFont;
	//creating fonts
	void Start();

	//functions
	//draw string
	void String(unsigned long font, int x, int y, Color color, const char* msg, ...);

};

/*hooks just paint traverse atm ofc but here's some more if you understand what your doing and want to expand:
void __stdcall hkOverrideView(CViewSetup* vsView);
void __stdcall hkCreateMove(int sequence_number, float input_sample_frametime, bool active);
void __stdcall hkFrameStageNotify(ClientFrameStage_t curStage);
void __fastcall hkDrawModelExecute(void* thisptr, void* edx, void* pRender, const void* &state, const ModelRenderInfo_t &pInfo, VMatrix *pCustomBoneToWorld);
*/
void __stdcall hkPaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce);
