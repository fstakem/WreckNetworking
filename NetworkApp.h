#ifndef NETWORK_APP_H
#define NETWORK_APP_H

#define WIN32_LEAN_AND_MEAN 1

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


class NetworkApp : public wxApp
{
public:
	virtual bool OnInit(void);
	virtual int OnExit(void);

private:

};

DECLARE_APP(NetworkApp)

#endif