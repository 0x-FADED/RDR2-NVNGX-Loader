#include "hooking.h"
#include "scanner.h"

void init()
{
	hook::nop((scanner::GetAddress(L"RDR2.exe", "E8 ? ? ? ? 4C 8B CB 48 8D 54 24 60", -0xD)), 6); // GPU check
	hook::put<uint8_t>(scanner::GetAddress(L"RDR2.exe", "80 3D ? ? ? ? ? 75 ? 41 8B CF", 6), 0x01); //signature check

}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		init();
	}

	return TRUE;
}

