#pragma once

#include "cMain.h"

class cApp : public wxApp {
public:
	virtual bool OnInit() override;
};
 
inline cMain* ref; // I am to dumb for all this,
                   // Don't do this but yeah...