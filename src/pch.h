#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <wx/wx.h>
#include <wx/taskbar.h>
#include <wx/notifmsg.h>

#include <windows.h>
#include <TlHelp32.h>

#include <fstream>
#include <string>
#include <algorithm>

#include "cApp.h"
#include "cMain.h"
#include "config.h"
#include "FixFilePerms.h"
#include "inject.h"

#include "icon/icon.xpm"