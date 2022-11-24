// dllmain.cpp : Defines the entry point for the DLL application.
#include "patterns/Hooking.Patterns.h"
#include "patterns/hooking.h"

void init()
{
	auto loc = hook::get_pattern<uint8_t>("E8 ? ? ? ? 4C 8B CB 48 8D 54 24 60", -0xD);
	hook::nop(loc, 6);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		init();
	}

	return TRUE;
}

