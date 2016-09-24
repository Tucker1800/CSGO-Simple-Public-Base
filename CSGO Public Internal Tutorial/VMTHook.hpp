#pragma once
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