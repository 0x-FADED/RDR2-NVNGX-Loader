#pragma once

#include <Windows.h>
#include <algorithm>
#include <string_view>
#include <stdexcept>
#include <vector>

namespace scanner
{
	uintptr_t GetAddress(const std::wstring_view moduleName, const std::string_view pattern, ptrdiff_t offset = 0);
	uintptr_t GetOffsetFromInstruction(const std::wstring_view moduleName, const std::string_view pattern, ptrdiff_t offset = 0);
}