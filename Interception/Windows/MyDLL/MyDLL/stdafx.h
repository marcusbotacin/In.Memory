// DLL-based, Function Hooker
// Goal: Evaluate the overhead of performing real-time memory scans
// Implemented By: Marcus Botacin
// Adapted From: Mhook Library Sample
// Generated Using: CMake

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// MD5 Function
#include<wincrypt.h>
#include<stdlib.h>
char* HashMD5(char* data, DWORD *result);

// DLL Exports
#define EXPORT comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__)