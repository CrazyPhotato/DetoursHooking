// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "HookCode.h"
#include "Functions.h"

// ================================= Target API Hooking On / Off Define ==================================
#define HOOK_VIRTUALALLOC 0
#define HOOK_NTPROTECTVIRTUALMEMORY 1

// =======================================================================================================
#define INSTALL_HOOK 1

// Install Detours Hook
VOID WINAPI Routine_InstallHook()
{
	DWORD_PTR dwErrorCode = 0;
	PDWORD_PTR vTable = NULL;

// KERNELBASE.VirtualAlloc Hook
#if HOOK_VIRTUALALLOC
	HMODULE hModule = NULL;
	hModule = LoadLibraryA("KERNELBASE.dll");

	if (!hModule)
	{
		OutputDebugStringA(": Cannot Load KERNELBASE.dll");
		return;
	}
	OutputDebugStringA(": Start Hooking VirtualAlloc()");
	
	// Original API Address 
	Original_VirtualAlloc = (Prototype_VirtualAlloc)GetProcAddress(hModule, "VirtualAlloc"); 

	InstallDetoursHook(&(PVOID&)Original_VirtualAlloc, (PVOID)Hooked_VirtualAlloc);
#endif

#if HOOK_NTPROTECTVIRTUALMEMORY
	HMODULE hModule = NULL;
	hModule = LoadLibraryA("ntdll.dll");

	if (!hModule)
	{
		OutputDebugStringA(": Cannot Load ntdll.dll");
		return;
	}
	OutputDebugStringA(": Start Hooking NtProtectVirtualMemory()");

	// Original API Address 
	Original_NtProtectVirtualMemory = (Prototype_NtProtectVirtualMemory)GetProcAddress(hModule, "NtProtectVirtualMemory");

	InstallDetoursHook(&(PVOID&)Original_NtProtectVirtualMemory, (PVOID)Hooked_NtProtectVirtualMemory);
#endif
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD_PTR dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hInstance);

		HANDLE hCreateThread = NULL;
		
#if INSTALL_HOOK
		// WIN API 훅을 위한 스레드 생성
		hCreateThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Routine_InstallHook, 0, 0, 0);
#endif
	}
    return TRUE;
}

