#include "pch.h"
#include "cApp.h"
#include "config.h"

wxIMPLEMENT_APP(cApp);

bool cApp::OnInit() {

    char* shut_up_VS = _getcwd(Globals::WORKING_DIR, FILENAME_MAX);
    config cfg;
    if (!cfg.loadConfig()) { //if error
        cfg.saveConfig();
    }

    ref = new cMain();
    ref->Show();
	return true;
}