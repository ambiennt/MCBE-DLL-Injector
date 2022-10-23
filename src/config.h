#include "pch.h"

namespace Globals {

    inline char WORKING_DIR[1024]{};
    inline bool USE_CUSTOM_PROC_NAME = false;
    inline const std::wstring NO_DLL_PATH_SELECTED_MSG{ L"Click \"Select\" to select a DLL file" };
    inline std::wstring DLL_PATH{};
    inline const std::wstring MCBE_PROC_NAME{ L"Minecraft.Windows.exe" };
    inline std::wstring PROC_NAME{ Globals::MCBE_PROC_NAME };

} //namespace Globals


class config {
    std::string path;
    //Config name and state
    std::wstring name;
    std::wstring value;

    // generated Config str
    std::wstring configstr;

    int analyseInt();
    bool analyzeBool();
    void analyzeState();
    std::wstring makeConfig();

public:
    config();

    bool loadConfig();
    bool saveConfig();
};