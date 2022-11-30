#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <memory>

namespace tomlConfig 
{

    struct tomlSettings 
    {
        // [nvngx_loader_options]
        bool Disable_NVNGX_Checks;
        bool Disable_DLSS_Sharpening_and_AutoExposure;
    };

    bool Initialize();
    bool LoadTomlFile(const std::wstring_view FilePath);

}

extern tomlConfig::tomlSettings Configuration;