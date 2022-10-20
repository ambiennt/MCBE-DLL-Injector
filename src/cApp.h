#pragma once


#include "cMain.h"


class cApp : public wxApp {
public:
	cMain* m_frame1;

	virtual bool OnInit();
};
 
extern cMain* ref;