#include "NetworkApp.h"
#include "MainFrame.h"

bool NetworkApp::OnInit(void)
{	
	MainFrame* mainFrame = new MainFrame(wxT("CVE Networking App"),wxDefaultPosition,wxSize(600,600));
	SetTopWindow(mainFrame);	
	return true;
}

int NetworkApp::OnExit(void)
{
	int returnCode = wxApp::OnExit();
	return returnCode;
}

IMPLEMENT_APP(NetworkApp)