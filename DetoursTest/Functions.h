#pragma once
#include "Headers.h"

// 함수 선언 헤더

BOOL InstallDetoursHook(PVOID* pfnOrigin, PVOID pfnHook); // Detours Hook 설치 함수
