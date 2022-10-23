#pragma once

#include "config.h"
#include "taskBarIcon.h"

class cMain : public wxFrame {
public:
	wxPanel *mainPanel = nullptr;
	wxButton *btn_Inject = nullptr;
	wxButton *btn_Select = nullptr;
	wxTextCtrl *txt_ProcName = nullptr;
	wxTextCtrl *txt_DllPath = nullptr;
	wxBoxSizer *sizer = nullptr;
	wxCheckBox *check_CustomTarget = nullptr;
	wxFileDialog *openDialog = nullptr;

	Config cfg;

	cMain();
	virtual ~cMain() override;

	static void OnInjectButtonExecute(wxCommandEvent &evt, cMain &ref);
	void OnInjectButton(wxCommandEvent &evt);
	void OnSelectButton(wxCommandEvent &evt);
	void OnCustomCheckBox(wxCommandEvent &evt);

	void updateGlobalVars();

	wxDECLARE_EVENT_TABLE();
};