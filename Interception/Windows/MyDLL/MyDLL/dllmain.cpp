// DLL-based, Function Hooker
// Goal: Evaluate the overhead of performing real-time memory scans
// Implemented By: Marcus Botacin
// Adapted From: Mhook Library Sample
// Generated Using: CMake

// hint: compile using release mode to avoid stack mismatch exceptions

// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

// All hooking tasks are outsourced to the mhook library
#include <mhook-lib/mhook.h>

// Control if hooks are active or not
BOOL hooked=FALSE;

// Hooking Functions
// Selected functions according to the chosen paper 

// ReadProcessMemory
typedef BOOL (WINAPI * _ReadProcessMemory)(HANDLE,LPCVOID,LPVOID,SIZE_T,SIZE_T*);
_ReadProcessMemory TrueReadProcessMemory = (_ReadProcessMemory)GetProcAddress(GetModuleHandle(L"kernel32"), "ReadProcessMemory");
// VirtualAlloc
typedef LPVOID (WINAPI * _VirtualAlloc)(LPVOID,SIZE_T,DWORD,DWORD);
_VirtualAlloc TrueVirtualAlloc = (_VirtualAlloc)GetProcAddress(GetModuleHandle(L"kernel32"), "VirtualAlloc");
// WriteProcessMemory
typedef BOOL (WINAPI * _WriteProcessMemory)(HANDLE, LPVOID, LPCVOID, SIZE_T, SIZE_T* );
_WriteProcessMemory TrueWriteProcessMemory = (_WriteProcessMemory)GetProcAddress(GetModuleHandle(L"kernel32"), "WriteProcessMemory");

// Just a wrapper for providing a compilable example
// In the paper implementation, directly invoke HashMD5
// having the function parameters as input
void check_md5()
{
	char *input="This is a Test";
	char *output;
	DWORD res;
	output = HashMD5(input, &res);
}

// Hooked Function
BOOL HookReadProcessMemory(HANDLE  hProcess, LPCVOID lpBaseAddress, LPVOID  lpBuffer, SIZE_T  nSize, SIZE_T  *lpNumberOfBytesRead)
{
	// The original paper implementation checks if data should be inspected or not using MD5
	check_md5();
	// The paper does not describe the communication step. Add it here if you have one.
	OutputDebugStringA("Custom ReadProcessMemory");
	// Invoke the original function
    return TrueReadProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead);
}

// Same as above
LPVOID HookVirtualAlloc(LPVOID lpAddress,SIZE_T dwSize,DWORD  flAllocationType,DWORD  flProtect)
{
	check_md5();
	OutputDebugStringA("Custom VirtualAlloc");
    return TrueVirtualAlloc(lpAddress,dwSize,flAllocationType,flProtect);
}

// Same as above
BOOL HookWriteProcessMemory(HANDLE  hProcess, LPVOID  lpBaseAddress, LPCVOID lpBuffer, SIZE_T  nSize, SIZE_T  *lpNumberOfBytesWritten)
{
	check_md5();
	OutputDebugStringA("Custom VirtualAlloc");
	return TrueWriteProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesWritten);
}

// Deploy the hooks
void hook()
{
	// Avoid trying to hook already-hooked functions
	if (hooked==FALSE)
	{
		// Select here 
		if (Mhook_SetHook((PVOID*)&TrueReadProcessMemory, (PVOID) HookReadProcessMemory)
			&& Mhook_SetHook((PVOID*)&TrueVirtualAlloc, (PVOID) HookVirtualAlloc)	
			&& Mhook_SetHook((PVOID*)&TrueWriteProcessMemory, (PVOID) HookWriteProcessMemory)	
		){
			hooked=TRUE;
			OutputDebugStringA("Hooked");
		}
	}
}

// Unhook hooked functions
void unhook()
{
	// Prevent double-unhook attempts
	if (hooked==TRUE)
	{
		Mhook_Unhook((PVOID*)&TrueReadProcessMemory);
		Mhook_Unhook((PVOID*)&TrueVirtualAlloc);
		hooked=FALSE;
		OutputDebugStringA("Unhooked");
	}
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	// Hook when attaching
	case DLL_PROCESS_ATTACH:
		OutputDebugStringA("Hello from DLL");
		hook();
		break;
	// Unhook when detaching
	case DLL_PROCESS_DETACH:
		OutputDebugStringA("Bye from DLL");
		unhook();
		break;
	}	
	return TRUE;
}