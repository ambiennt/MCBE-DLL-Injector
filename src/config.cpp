#include "pch.h"

#include "config.h"

#include <fstream>
#include <algorithm>
#include <direct.h>

config::config() {
    this->path = Globals::WORKING_DIR;
    this->path += "\\config.txt";
}

bool config::loadConfig() {
    std::wifstream cFile(this->path);

    if (cFile.is_open()) {
        std::wstring line;
        while (std::getline(cFile, line)) {

            if (line[0] == '#' || line.empty()) {
                continue;
            }

            size_t delimiterPos = line.find('=');
            this->name = line.substr(0, delimiterPos);

            this->value = line.substr(delimiterPos + 1);
            // std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) { return std::tolower(c); });
            this->analyzeState();
        }
        return true;
    }

    // can't load config file, so we generate a new one via config::saveConfig
    return false;
}

bool config::saveConfig() {
    std::wofstream create(this->path);
    if (create.is_open()) {
        std::wstring configstr = this->makeConfig();
        create << configstr;
    }
    else {
        wxMessageBox("Can't create config file!", "ERROR", wxICON_ERROR);
        return false;
    }

    return true;
}

bool config::analyzeBool() {
    std::transform(this->value.begin(), this->value.end(), this->value.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return ((this->value == "true") || (this->value == "1"));
}

int config::analyseInt() {
    if (std::all_of(this->value.begin(), this->value.end(), ::isdigit)) {
        return std::stoi(this->value);
    }
    return 0;
}

std::wstring config::makeConfig() {

    this->configstr += L"# MCBE DLL injector config\n";

    // useCustomProcName
    this->configstr += Globals::USE_CUSTOM_PROC_NAME ? L"useCustomProcName=true\n" : L"useCustomProcName=false\n";
    // dllPath
    this->configstr += L"dllPath=" + Globals::DLL_PATH + '\n';
    // procName
    this->configstr += L"procName=" + Globals::PROC_NAME + '\n';

    return this->configstr;
}

void config::analyzeState() {
    if (this->name == "useCustomProcName") {
        Globals::USE_CUSTOM_PROC_NAME = this->analyzeBool();
    }
    else if (this->name == "dllPath") {
        Globals::DLL_PATH = this->value;
    }
    else if (this->name == "procName") {
        Globals::PROC_NAME = this->value;
    }
    else {
        wxMessageBox("\"" + this->name + "\" is not a known entry\nDeleting the config file might help!", "WARNING", wxICON_INFORMATION);
    }
}