// DLL-based, Function Hooker
// Goal: Evaluate the overhead of performing real-time memory scans
// Implemented By: Marcus Botacin
// Adapted From: Mhook Library Sample
// Generated Using: CMake

// MyDLL.cpp : Defines the exported functions for the DLL application.

#include "stdafx.h"

// This is a Simple Test Function to test the library loading via rundll process
void test(void)
{
#pragma EXPORT
	OutputDebugStringA("This is Just a Test");
}

// This is a MD5 wrapper for the the MS crypto library
char* HashMD5(char* data, DWORD *result)
{
    DWORD dwStatus = 0;
    DWORD cbHash = 16;
    int i = 0;
    HCRYPTPROV cryptProv;
    HCRYPTHASH cryptHash;
    BYTE hash[16];
    char *hex = "0123456789abcdef";
    char *strHash;
    strHash = (char*)malloc(500);
    memset(strHash, '\0', 500);
    if (!CryptAcquireContext(&cryptProv, NULL, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
    {
        dwStatus = GetLastError();
        *result = dwStatus;
        return NULL;
    }
    if (!CryptCreateHash(cryptProv, CALG_MD5, 0, 0, &cryptHash))
    {
        dwStatus = GetLastError();
        CryptReleaseContext(cryptProv, 0);
        *result = dwStatus;
        return NULL;
    }
    if (!CryptHashData(cryptHash, (BYTE*)data, strlen(data), 0))
    {
        dwStatus = GetLastError();
        CryptReleaseContext(cryptProv, 0);
        CryptDestroyHash(cryptHash);
        *result = dwStatus;
        return NULL;
    }
    if (!CryptGetHashParam(cryptHash, HP_HASHVAL, hash, &cbHash, 0))
    {
        dwStatus = GetLastError();
        CryptReleaseContext(cryptProv, 0);
        CryptDestroyHash(cryptHash);
        *result = dwStatus;
        return NULL;
    }
    for (i = 0; i < cbHash; i++)
    {
        strHash[i * 2] = hex[hash[i] >> 4];
        strHash[(i * 2) + 1] = hex[hash[i] & 0xF];
    }
    CryptReleaseContext(cryptProv, 0);
    CryptDestroyHash(cryptHash);
    return strHash;
}