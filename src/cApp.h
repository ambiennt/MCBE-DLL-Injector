#pragma once

#include "config.h"

class cMain;

class cApp : public wxApp {
public:
	virtual bool OnInit() override;
};

inline cMain* CMAIN_INSTANCE{};