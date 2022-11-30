#include "hooking.h"
#include "scanner.h"
#include "toml++.h"


void init()
{
	tomlConfig::Initialize();

	if(Configuration.Disable_NVNGX_Checks)
	{
		hook::nop((scanner::GetAddress(L"RDR2.exe", "E8 ? ? ? ? 4C 8B CB 48 8D 54 24 60", -0xD)), 6); // GPU check
		hook::put<uint8_t>(scanner::GetAddress(L"RDR2.exe", "80 3D ? ? ? ? ? 75 ? 41 8B CF", 6), 0x01); //signature check
	}

		 if(Configuration.Disable_DLSS_Sharpening_and_AutoExposure)
		 {			   
			 /*
			 * gets addresss of the function we are patching form the calls the offset is function + 0xA9
			 * we cant search originial bytes because of 3 matches 1st match is crashlog related shit
			 * originial bytes 44 8B 43 14 48 8D 15 ? ? ? ?
			 * mov r8d, dword ptr ds:[rbx+0x14] 
			 * lea rdx, DLSS.Feature.Create.Flags
			 */
			 auto loc = scanner::GetOffsetFromInstruction(L"RDR2.exe", "E8 ? ? ? ? EB ? E8 ? ? ? ? 48 ? C8 48 89", 1); // VULKAN
			 auto addr = scanner::GetOffsetFromInstruction(L"RDR2.exe", "8B D7 E8 ? ? ? ? 44 ? D8", 3); // DirectX12

			 /*
			 * patched bytes: 41 B0 4B 90 48 8D 15 ? ? ? ?
			 * mov r8b, 0x4B
			 * nop
			 * lea rdx, DLSS.Feature.Create.Flags
			 */
			 constexpr const uint8_t patchBytes[]{ 0x41, 0xB0, 0x4B, 0x90, 0x48, 0x8D, 0x15 };
			 
			 hook::patch((loc + 0xA9), patchBytes);
			 
			 hook::patch((addr + 0xA9), patchBytes);
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

