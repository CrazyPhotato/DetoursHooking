#include "Functions.h"

// Install Detours Hook
// pfnOrigin : Target API / pfnHook : HookFunction
BOOL InstallDetoursHook(PVOID* pfnOrigin, PVOID pfnHook)
{
	DWORD_PTR dwErrorCode = 0;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	dwErrorCode = DetourAttach(pfnOrigin, (PVOID)pfnHook);
	if (dwErrorCode)
	{
		return false;
	}
	DetourTransactionCommit();

	return true;
}