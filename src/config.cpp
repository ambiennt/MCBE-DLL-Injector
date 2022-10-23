#include "pch.h"
#include "config.h"

Config::Config() {
    this->path = Globals::WORKING_DIR;
    this->path += "\\config.txt";
}

bool Config::serializeConfig() {
    std::wifstream cFile(this->path);

    if (cFile.is_open()) {
        std::wstring currLine;
        while (std::getline(cFile, currLine)) {

            if (currLine.empty() || currLine[0] == '#') {
                continue;
            }

            size_t delimiterPos = currLine.find('=');
            this->currentKey = currLine.substr(0, delimiterPos);

            this->currentVal = currLine.substr(delimiterPos + 1);
            // std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) { return std::tolower(c); });
            this->analyzeState();
        }

        cFile.close();
        return true;
    }

    // can't load config file, so we generate a new one via Config::updateConfigFile with default globals
    return false;
}

bool Config::analyzeBool() {
    std::transform(this->currentVal.begin(), this->currentVal.end(), this->currentVal.begin(), [](wchar_t c) {
        return std::tolower(static_cast<int>(c));
    });
    return (this->currentVal == "true") || (this->currentVal == "1");
}

int Config::analyzeInt() {
    if (std::all_of(this->currentVal.begin(), this->currentVal.end(), ::isdigit)) {
        return std::stoi(this->currentVal);
    }
    return 0;
}

bool Config::updateConfigFile() const {
    std::wofstream cfgStream(this->path, std::ios::trunc);
    if (cfgStream.is_open()) {
        cfgStream << L"# MCBE DLL injector config\n";
        cfgStream << (Globals::USE_CUSTOM_PROC_NAME ? L"useCustomProcName=true\n" : L"useCustomProcName=false\n");
        cfgStream << L"dllPath=" + Globals::DLL_PATH + '\n';
        cfgStream << L"procName=" + Globals::PROC_NAME + '\n';

        cfgStream.close();
        return true;
    }
    return false;
}

void Config::analyzeState() {
    if (this->currentKey == "useCustomProcName") {
        Globals::USE_CUSTOM_PROC_NAME = this->analyzeBool();
    }
    else if (this->currentKey == "dllPath") {
        Globals::DLL_PATH = this->currentVal;
    }
    else if (this->currentKey == "procName") {
        Globals::PROC_NAME = this->currentVal;
    }
    else {
        wxMessageBox("\"" + this->currentKey + "\" is not a known entry\nDeleting the config file might help!", "WARNING", wxICON_INFORMATION);
    }
}