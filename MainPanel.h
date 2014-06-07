#ifndef MAIN_PANEL_H
#define MAIN_PANEL_H

#define WIN32_LEAN_AND_MEAN 1

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include "Session.h"
#include "Messenger.h"
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class MainPanel : public wxPanel 
{
	public:
		MainPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
		~MainPanel();

	private:
		// UI elements generated
		wxStaticText* portLabel;
		wxTextCtrl* serverTextCtrl;
		wxButton* startStopButton;
		wxStaticText* remoteHostLabel;
		wxTextCtrl* remoteHostTextCtrl;
		wxStaticText* remotePortLabel;
		wxTextCtrl* remotePortTextCtrl;
		wxStaticText* hostLabel;
		wxTextCtrl* hostTextCtrl;
		wxStaticText* packetLabel;
		wxComboBox* packetComboBox;
		wxStaticText* timestampLabel;
		wxTextCtrl* timestampTextCtrl;
		wxStaticText* seqNumLabel;
		wxTextCtrl* seqNumTextCtrl;
		wxStaticText* entityLabel;
		wxTextCtrl* entityTextCtrl;
		wxStaticText* stateLabel;
		wxTextCtrl* stateTextCtrl;
		wxStaticText* positionLabel;
		wxStaticText* pxLabel;
		wxTextCtrl* pxTextCtrl;
		wxStaticText* pyLabel;
		wxTextCtrl* pyTextCtrl;
		wxStaticText* pzLabel;
		wxTextCtrl* pzTextCtrl;
		wxStaticText* velocityLabel;
		wxStaticText* vxLabel;
		wxTextCtrl* vxTextCtrl;
		wxStaticText* vyLabel;
		wxTextCtrl* vyTextCtrl;
		wxStaticText* vzLabel;
		wxTextCtrl* vzTextCtrl;
		wxStaticText* accelerationLabel;
		wxStaticText* axLabel;
		wxTextCtrl* axTextCtrl;
		wxStaticText* ayLabel;
		wxTextCtrl* ayTextCtrl;
		wxStaticText* azLabel;
		wxTextCtrl* azTextCtrl;
		wxStaticText* txTextLabel;
		wxTextCtrl* txTextCtrl;
		wxButton* txButton;
		wxTextCtrl* connectTextCtrl;

		// Network elements
		boost::shared_ptr<Messenger> messenger;
		std::vector<Session> sessions;
		
		// UI events generated
		virtual void onCharNumOnly( wxKeyEvent& event );
		virtual void startStopMessenger( wxCommandEvent& event );
		virtual void onCharIpAddr( wxKeyEvent& event );
		virtual void sendMsg( wxCommandEvent& event );

		// UI events hand done
		virtual void onIdle(wxIdleEvent& event);

		// Helper functions
		std::string MainPanel::getDataFromInterface();
		void MainPanel::getPacketInformation(HeaderInformation& header);
		void MainPanel::getDataFromTrackers(std::vector<EntityInformation>& entities);
};

#endif
