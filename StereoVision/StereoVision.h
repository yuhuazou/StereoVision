// StereoVision.h : main header file for the PROJECT_NAME application
//

#pragma once
//#pragma comment(lib,"libSaveVideo.lib")

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif


#include "resource.h"		// main symbols

// CStereoVisionApp:
// See StereoVision.cpp for the implementation of this class
//

class CStereoVisionApp : public CWinApp
{
public:
	CStereoVisionApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CStereoVisionApp theApp;
