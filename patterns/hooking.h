#pragma once
#include <Windows.h>

namespace hook
{
	template<typename AddressType>
	inline void nop(AddressType address, size_t length)
	{

		DWORD oldProtect;
		VirtualProtect((void*)address, length, PAGE_EXECUTE_READWRITE, &oldProtect);

		memset((void*)address, 0x90, length);

		VirtualProtect((void*)address, length, oldProtect, &oldProtect);
		FlushInstructionCache(GetCurrentProcess(), (void*)address, length);
	}
}