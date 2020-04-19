// Memory AV prototype
// Sample implementation of a hooking mechanism for on-access memory scan
// Created by: Marcus Botacin

#define _GNU_SOURCE
#include<string.h>
#include <dlfcn.h>
#include<stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>

// function to be hooked
typedef void* (*orig_memcpy_type)(void *dest, const void *src, size_t n);
// recursion depth
int level = 0;	

// hooked function
void *memcpy(void *dest, const void *src, size_t n)
{
	char digest[MD5_DIGEST_LENGTH];
	orig_memcpy_type orig_memcpy;
	// get original function address
  	orig_memcpy = (orig_memcpy_type)dlsym(RTLD_NEXT,"memcpy");
	// do not allow recursive application (MD5 calls memcpy)
	if (!level)
	{
		// dig into new call
		level++;
		// original paper relies on MD5 for uniqueness
		MD5(src, n, digest);
		// return from lower depths
		level--;
	}
	// call the original function
  	return orig_memcpy(dest,src,n);
}
