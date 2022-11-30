#include "..\dependencies\tomlplusplus\include\toml++\toml.h"

#include "toml++.h"

tomlConfig::tomlSettings Configuration;
namespace tomlConfig 
{

    tomlSettings ParseSettings(const toml::table& Table);

    bool Initialize() 
    {
        return LoadTomlFile(L"nvngx_loader.toml");
    }

    bool LoadTomlFile(const std::wstring_view FilePath) 
    {
        toml::table table;

        try 
        {
            table = toml::parse_file(L"nvngx_loader.toml");
        }
        catch (const toml::parse_error&) 
        {
            return false;
        }

        Configuration = ParseSettings(table);
        return true;
    }

#define PARSE_TOML_MEMBER(obj, x) g_tomlSettings.x = ( * obj)[#x].value_or(decltype(g_tomlSettings.x) {})

    tomlSettings ParseSettings(const toml::table& Table) 
    {
        tomlSettings g_tomlSettings;

        // [nvngx_loader_options]
        if (auto nvngx_loader_options = Table[L"nvngx_loader_options"].as_table()) 
        {
            PARSE_TOML_MEMBER(nvngx_loader_options, Disable_NVNGX_Checks);
            PARSE_TOML_MEMBER(nvngx_loader_options, Disable_DLSS_Sharpening_and_AutoExposure);
        }

        return g_tomlSettings;
    }
#undef PARSE_TOML_MEMBER

}