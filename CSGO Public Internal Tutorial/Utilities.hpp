#pragma once
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