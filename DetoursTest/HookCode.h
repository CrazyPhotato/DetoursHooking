#pragma once
#include "Headers.h"

typedef struct _OBJECT_ATTRIBUTES {
	ULONG Length;
	HANDLE RootDirectory;
	PUNICODE_STRING ObjectName;
	ULONG Attributes;
	PVOID SecurityDescriptor;
	PVOID SecurityQualityOfService;
} OBJECT_ATTRIBUTES;
typedef OBJECT_ATTRIBUTES* POBJECT_ATTRIBUTES;
typedef CONST OBJECT_ATTRIBUTES* PCOBJECT_ATTRIBUTES;

// --------------------------------------- Function Declaration ---------------------------------------

// WIN API Hook Code Functions
HRESULT WINAPI Hooked_VirtualAlloc(LPVOID , SIZE_T , DWORD , DWORD );
NTSTATUS NTAPI Hooked_NtProtectVirtualMemory(HANDLE , PVOID* , PULONG , ULONG , PULONG );

// WIN API Prototype
typedef HRESULT(WINAPI* Prototype_VirtualAlloc)(LPVOID, SIZE_T, DWORD, DWORD);
typedef DWORD(NTAPI* Prototype_NtProtectVirtualMemory)(HANDLE, PVOID, PULONG, ULONG, PULONG);
// --------------------------------------- Extern Global Variable ---------------------------------------

// WIN API Original Function Pointer
extern Prototype_VirtualAlloc Original_VirtualAlloc;
extern Prototype_NtProtectVirtualMemory Original_NtProtectVirtualMemory;