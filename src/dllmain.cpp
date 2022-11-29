#include "hooking.h"
#include "scanner.h"

//todo - maybe someday learn rust and re-write this shit in rust

void init() // mod initilization this mod can be used standalone of you want to get rid of the oversharpned DLSS or it's bad auto exposure..x)
{
	static int val = GetPrivateProfileIntW(L"nvngx_loader_options", L"Disable_sharpening_and_auto_exposure", 0, L".\\nvngx_loader.toml");

	hook::nop((scanner::GetAddress(L"RDR2.exe", "E8 ? ? ? ? 4C 8B CB 48 8D 54 24 60", -0xD)), 6); // GPU check
	hook::put<uint8_t>(scanner::GetAddress(L"RDR2.exe", "80 3D ? ? ? ? ? 75 ? 41 8B CF", 6), 0x01); //signature check

	
	if (val != 0)
	{
		// gets addresss of the function we are patching form the calls the offset is function + 0xA9
		// we cant search originial bytes because of 3 matches 1st match is crashlog shit
		// originial bytes 44 8B 43 14 48 8D 15 ? ? ? ?
		// mov r8d, dword ptr ds:[rbx+0x14] 
		// lea rdx, DlssFeatureCreateFlagChar ; "DLSS.Feature.Create.Flags"
		
		auto addr = scanner::GetOffsetFromInstruction(L"RDR2.exe", "E8 ? ? ? ? 44 8B D8 48 8B 5C 24 40", 1); 
		auto loc = scanner::GetOffsetFromInstruction(L"RDR2.exe", "E8 ? ? ? ? EB ? E8 ? ? ? ? 48 8B C8 48 89", 1);

		// patched bytes: 41 B0 4B 90 48 8D 15 ? ? ? ?
		// mov r8b, 0x4B
		// nop
		// lea rdx, DlssFeatureCreateFlagChar ; "DLSS.Feature.Create.Flags"
		constexpr uint8_t patchBytes[]{ 0x41, 0xB0, 0x4B, 0x90, 0x48, 0x8D, 0x15 };

		hook::patch((addr + 0xA9), patchBytes);
		hook::patch((loc + 0xA9), patchBytes);
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		init();
	}

	return TRUE;
}

