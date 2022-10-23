#include "pch.h"
#include "cMain.h"
#include"FixFilePerms.h"
#include "inject.h"
#include "cApp.h"
#include "config.h"
#include "icon/icon.xpm"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_BUTTON(101, OnInjectButton)
EVT_BUTTON(102, OnSelectButton)

EVT_CHECKBOX(201, OnCustomCheckBox)

wxEND_EVENT_TABLE();


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "MCBE DLL Injector", wxDefaultPosition, wxSize(297.5, 162.5), wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN) {
    wxIcon icon(icon_xpm); // icons are shit to do but the technike is actually quite nice
    this->SetIcon(icon);
    this->SetBackgroundColour(wxColour(255, 255, 255, 255));

    this->mainPanel = new wxPanel(this, wxID_ANY);
    this->btn_Inject = new wxButton(this->mainPanel, 101, "Inject", wxPoint(5, 9), wxSize(100, 48));
    this->btn_Select = new wxButton(this->mainPanel, 102, "Select", wxPoint(5, 66), wxSize(60, 25));
    this->txt_ProcName = new wxTextCtrl(this->mainPanel, wxID_ANY, Globals::PROC_NAME, wxPoint(110, 10), wxSize(165, 23));
    this->check_CustomTarget = new wxCheckBox(this->mainPanel, 201, "Custom Target", wxPoint(110, 40), wxSize(165, 20));
    this->txt_DllPath = new wxTextCtrl(
        this->mainPanel, wxID_ANY,
        (Globals::DLL_PATH.empty() ? Globals::NO_DLL_PATH_SELECTED_MSG : Globals::DLL_PATH),
        wxPoint(70, 67), wxSize(205, 23)
    );
    
    this->CreateStatusBar(1);
    this->SetStatusText("Version 1.1", 0);

    if (Globals::USE_CUSTOM_PROC_NAME) {
        this->txt_ProcName->Enable();
    }
    else {
        this->txt_ProcName->Disable();
    }
    
    this->openDialog = new wxFileDialog(this, "Select the .dll file", Globals::WORKING_DIR, "*.dll" ,"Dynamic link library (*.dll)|*.dll", wxFD_OPEN);
}

cMain::~cMain() {
    this->openDialog->Destroy();
}

void cMain::OnInjectButton(wxCommandEvent& evt) {
    cMain::OnInjectButtonExecute(evt, this);
}

void cMain::OnInjectButtonExecute(wxCommandEvent& evt, cMain* ref) {
    std::string debug;

    DWORD procId = 0;

    procId = GetProcId(ref->txt_ProcName->GetValue().mb_str());


    if (procId == 0) {

        debug = "Can't find process! | " + std::to_string(procId);
        ref->SetStatusText(debug, 0);
        return;
    }
    wxString wxStrPath = ref->txt_DllPath->GetValue();
    std::wstring wStrPath = wxStrPath.ToStdWstring(); // converting wxstr to wstr
    std::ifstream test(wStrPath.c_str()); // test if file path is valid
    if (!test) {

        debug = "Process found! | " + std::to_string(procId) + " | invalid file path";
        ref->SetStatusText(debug, 0);
        return;
    }

    SetAccessControl(wStrPath, L"S-1-15-2-1");
    performInjection(procId, wStrPath.c_str());
    debug = "Process found! | " + std::to_string(procId) + " | valid file path | Injected!";
    ref->SetStatusText(debug, 0);


    // update globals and config...
    Globals::USE_CUSTOM_PROC_NAME = ref->check_CustomTarget->GetValue();
    Globals::DLL_PATH = ref->txt_DllPath->GetValue();
    Globals::PROC_NAME = ref->txt_ProcName->GetValue();

    config cfg;
    cfg.saveConfig();

	evt.Skip();
}

void cMain::OnSelectButton(wxCommandEvent& evt) {
    if (this->openDialog->ShowModal() == wxID_OK) { // if the user click "Open" instead of "Cancel"
        this->txt_DllPath->SetLabel(this->openDialog->GetPath());
    }
	evt.Skip();
}

void cMain::OnCustomCheckBox(wxCommandEvent& evt) {
    if (this->check_CustomTarget->IsChecked()) {
        this->txt_ProcName->Enable(true);
    }
    else {
        this->txt_ProcName->Enable(false);
        this->txt_ProcName->SetLabel(Globals::MCBE_PROC_NAME);
    }
    evt.Skip();
}