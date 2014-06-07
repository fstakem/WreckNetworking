#include "MainFrame.h"
#include "MainPanel.h"

MainFrame::MainFrame(wxString const & title, wxPoint const & pos, wxSize const & size)
: wxFrame(0,-1,title,pos,size)
{
	#if defined(__WXDEBUG__ )
    //Debug window
	wxLogWindow* logWindow = new wxLogWindow(this, "Log Window", true, true);
	wxLog::SetActiveTarget(logWindow);
	#endif

	MainPanel* mainPanel = new MainPanel(this, wxID_ANY,
										 wxDefaultPosition, 
										 wxSize(600, 600));

	this->Show();
}

MainFrame::~MainFrame(void) 
{	

}
