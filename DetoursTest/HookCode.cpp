// ���� ��ŷ �Լ� ���� �ڵ���� ������ ��ġ
#include "HookCode.h"
#include "Functions.h"

// WIN API Functions
Prototype_VirtualAlloc Original_VirtualAlloc = NULL;
Prototype_NtProtectVirtualMemory Original_NtProtectVirtualMemory = NULL;

// ��ŷ�� ���������� ����Ǿ����� üũ�ϱ� ���� �÷���
BOOL bHookCodeLog_VirtualAlloc = FALSE;
BOOL bHookCodeLog_NtProtectVirtualMemory = FALSE;

// VirtualAlloc ��ŷ�Լ�
HRESULT WINAPI Hooked_VirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect)
{
	if (bHookCodeLog_VirtualAlloc == FALSE)
	{
		OutputDebugStringA("[TEST MODULE] : VirtualAlloc() Hook Code Running");
		bHookCodeLog_VirtualAlloc = TRUE;
	}
	return Original_VirtualAlloc(lpAddress, dwSize, flAllocationType, flProtect);
}

NTSTATUS NTAPI Hooked_NtProtectVirtualMemory(HANDLE ProcessHandle, PVOID* BaseAddress, PULONG NumberOfBytesToProtect, ULONG NewAccessProtection, PULONG OldAccessProtection)
{
	if (bHookCodeLog_NtProtectVirtualMemory == FALSE)
	{
		OutputDebugStringA("[TEST MODULE] : NtProtectVirtualMemory() Hook Code Running");
		bHookCodeLog_NtProtectVirtualMemory = TRUE;
	}
	return Original_NtProtectVirtualMemory(ProcessHandle, BaseAddress, NumberOfBytesToProtect, NewAccessProtection, OldAccessProtection);
}