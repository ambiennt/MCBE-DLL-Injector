#include "pch.h"
#include "cApp.h"

wxIMPLEMENT_APP(cApp);

bool cApp::OnInit() {

    char* shut_up_VS = _getcwd(Globals::WORKING_DIR, FILENAME_MAX);

    CMAIN_INSTANCE = new cMain();

    if (!CMAIN_INSTANCE->cfg.serializeConfig()) { //if error
        CMAIN_INSTANCE->cfg.updateConfigFile();
    }

    CMAIN_INSTANCE->Show();
	return true;
}