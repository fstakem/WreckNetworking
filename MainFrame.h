#ifndef MAIN_FRAME_H
#define MAIN_FRAME_H

#define WIN32_LEAN_AND_MEAN 1

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

class MainFrame : public wxFrame
{
public:
	MainFrame(wxString const& title, wxPoint const& pos, wxSize const& size);
	~MainFrame(void);

private:

};

#endif