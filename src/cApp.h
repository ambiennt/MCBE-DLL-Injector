#pragma once

#include "config.h"
#include "cMain.h"
#include <memory>

class cApp : public wxApp {
public:
	virtual bool OnInit() override;
};

inline cMain* CMAIN_INSTANCE{};