#include "MainPanel.h"
#include <sstream>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include "Core.h"
#include "StateInformation.h"
#include "EntityInformation.h"
#include "HeaderInformation.h"


MainPanel::MainPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : 
wxPanel( parent, id, pos, size, style ), messenger()
{
	this->SetExtraStyle( wxWS_EX_PROCESS_IDLE );
	
	wxBoxSizer* panelSizer;
	panelSizer = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* serverSizer;
	serverSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Server") ), wxVERTICAL );
	
	wxBoxSizer* portSizer;
	portSizer = new wxBoxSizer( wxHORIZONTAL );
	
	portLabel = new wxStaticText( this, wxID_ANY, wxT("Port"), wxDefaultPosition, wxDefaultSize, 0 );
	portLabel->Wrap( -1 );
	portSizer->Add( portLabel, 0, wxALIGN_CENTER|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	serverTextCtrl = new wxTextCtrl( this, wxID_ANY, wxT("3500"), wxDefaultPosition, wxSize( 50,20 ), wxTE_PROCESS_ENTER );
	portSizer->Add( serverTextCtrl, 1, wxALIGN_CENTER|wxALL, 5 );
	
	serverSizer->Add( portSizer, 1, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	startStopButton = new wxButton( this, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	serverSizer->Add( startStopButton, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	panelSizer->Add( serverSizer, 5, wxALL|wxEXPAND, 12 );
	
	wxStaticBoxSizer* txSizer;
	txSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Transmission") ), wxHORIZONTAL );
	
	wxBoxSizer* txHostSizer;
	txHostSizer = new wxBoxSizer( wxVERTICAL );
	
	remoteHostLabel = new wxStaticText( this, wxID_ANY, wxT("IP"), wxDefaultPosition, wxDefaultSize, 0 );
	remoteHostLabel->Wrap( -1 );
	txHostSizer->Add( remoteHostLabel, 0, wxALL, 5 );
	
	remoteHostTextCtrl = new wxTextCtrl( this, wxID_ANY, wxT("127.0.0.1"), wxDefaultPosition, wxSize( 80,20 ), 0 );
	txHostSizer->Add( remoteHostTextCtrl, 1, wxALL, 5 );
	
	remotePortLabel = new wxStaticText( this, wxID_ANY, wxT("Port"), wxDefaultPosition, wxDefaultSize, 0 );
	remotePortLabel->Wrap( -1 );
	txHostSizer->Add( remotePortLabel, 0, wxALL, 5 );
	
	remotePortTextCtrl = new wxTextCtrl( this, wxID_ANY, wxT("3501"), wxDefaultPosition, wxSize( 60,20 ), 0 );
	txHostSizer->Add( remotePortTextCtrl, 1, wxALL, 5 );
	
	txSizer->Add( txHostSizer, 1, wxALL, 4 );
	
	wxBoxSizer* txDataSizer;
	txDataSizer = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* txDataSizer2;
	txDataSizer2 = new wxFlexGridSizer( 3, 4, 0, 0 );
	txDataSizer2->SetFlexibleDirection( wxBOTH );
	txDataSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	hostLabel = new wxStaticText( this, wxID_ANY, wxT("Host Handle"), wxDefaultPosition, wxDefaultSize, 0 );
	hostLabel->Wrap( -1 );
	txDataSizer2->Add( hostLabel, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	hostTextCtrl = new wxTextCtrl( this, wxID_ANY, wxT("Alpha"), wxDefaultPosition, wxDefaultSize, 0 );
	txDataSizer2->Add( hostTextCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	packetLabel = new wxStaticText( this, wxID_ANY, wxT("Packet Type"), wxDefaultPosition, wxDefaultSize, 0 );
	packetLabel->Wrap( -1 );
	txDataSizer2->Add( packetLabel, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	packetComboBox = new wxComboBox( this, wxID_ANY, wxT("Connect"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN );
	packetComboBox->Append( wxT("Connect") );
	packetComboBox->Append( wxT("ConnectAck") );
	packetComboBox->Append( wxT("StateUpdate") );
	packetComboBox->Append( wxT("Disconnect") );
	packetComboBox->Append( wxT("DisconnectAck") );
	txDataSizer2->Add( packetComboBox, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL|wxEXPAND, 5 );
	
	timestampLabel = new wxStaticText( this, wxID_ANY, wxT("Timestamp"), wxDefaultPosition, wxDefaultSize, 0 );
	timestampLabel->Wrap( -1 );
	txDataSizer2->Add( timestampLabel, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	timestampTextCtrl = new wxTextCtrl( this, wxID_ANY, wxT("1000"), wxDefaultPosition, wxDefaultSize, 0 );
	txDataSizer2->Add( timestampTextCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	seqNumLabel = new wxStaticText( this, wxID_ANY, wxT("Sequence Number"), wxDefaultPosition, wxDefaultSize, 0 );
	seqNumLabel->Wrap( -1 );
	txDataSizer2->Add( seqNumLabel, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	seqNumTextCtrl = new wxTextCtrl( this, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, 0 );
	txDataSizer2->Add( seqNumTextCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL|wxEXPAND, 5 );
	
	entityLabel = new wxStaticText( this, wxID_ANY, wxT("Entity Handle"), wxDefaultPosition, wxDefaultSize, 0 );
	entityLabel->Wrap( -1 );
	txDataSizer2->Add( entityLabel, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	entityTextCtrl = new wxTextCtrl( this, wxID_ANY, wxT("Red Dog"), wxDefaultPosition, wxDefaultSize, 0 );
	txDataSizer2->Add( entityTextCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	stateLabel = new wxStaticText( this, wxID_ANY, wxT("State Handle"), wxDefaultPosition, wxDefaultSize, 0 );
	stateLabel->Wrap( -1 );
	txDataSizer2->Add( stateLabel, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	stateTextCtrl = new wxTextCtrl( this, wxID_ANY, wxT("Arm"), wxDefaultPosition, wxDefaultSize, 0 );
	txDataSizer2->Add( stateTextCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL|wxEXPAND, 5 );
	
	txDataSizer->Add( txDataSizer2, 3, wxEXPAND, 5 );
	
	wxFlexGridSizer* txDataSizer3;
	txDataSizer3 = new wxFlexGridSizer( 3, 7, 0, 0 );
	txDataSizer3->SetFlexibleDirection( wxBOTH );
	txDataSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	positionLabel = new wxStaticText( this, wxID_ANY, wxT("Position"), wxDefaultPosition, wxDefaultSize, 0 );
	positionLabel->Wrap( -1 );
	txDataSizer3->Add( positionLabel, 0, wxALIGN_CENTER|wxALL, 5 );
	
	pxLabel = new wxStaticText( this, wxID_ANY, wxT("x"), wxDefaultPosition, wxDefaultSize, 0 );
	pxLabel->Wrap( -1 );
	txDataSizer3->Add( pxLabel, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	pxTextCtrl = new wxTextCtrl( this, wxID_ANY, wxT("1.1"), wxDefaultPosition, wxSize( 50,20 ), 0 );
	txDataSizer3->Add( pxTextCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	pyLabel = new wxStaticText( this, wxID_ANY, wxT("y"), wxDefaultPosition, wxDefaultSize, 0 );
	pyLabel->Wrap( -1 );
	txDataSizer3->Add( pyLabel, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	pyTextCtrl = new wxTextCtrl( this, wxID_ANY, wxT("2.2"), wxDefaultPosition, wxSize( 50,20 ), 0 );
	txDataSizer3->Add( pyTextCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	pzLabel = new wxStaticText( this, wxID_ANY, wxT("z"), wxDefaultPosition, wxDefaultSize, 0 );
	pzLabel->Wrap( -1 );
	txDataSizer3->Add( pzLabel, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	pzTextCtrl = new wxTextCtrl( this, wxID_ANY, wxT("3.3"), wxDefaultPosition, wxSize( 50,20 ), 0 );
	txDataSizer3->Add( pzTextCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	velocityLabel = new wxStaticText( this, wxID_ANY, wxT("Velocity"), wxDefaultPosition, wxDefaultSize, 0 );
	velocityLabel->Wrap( -1 );
	txDataSizer3->Add( velocityLabel, 0, wxALIGN_CENTER|wxALL, 5 );
	
	vxLabel = new wxStaticText( this, wxID_ANY, wxT("x"), wxDefaultPosition, wxDefaultSize, 0 );
	vxLabel->Wrap( -1 );
	txDataSizer3->Add( vxLabel, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	vxTextCtrl = new wxTextCtrl( this, wxID_ANY, wxT("4.4"), wxDefaultPosition, wxSize( 50,20 ), 0 );
	txDataSizer3->Add( vxTextCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	vyLabel = new wxStaticText( this, wxID_ANY, wxT("y"), wxDefaultPosition, wxDefaultSize, 0 );
	vyLabel->Wrap( -1 );
	txDataSizer3->Add( vyLabel, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	vyTextCtrl = new wxTextCtrl( this, wxID_ANY, wxT("5.5"), wxDefaultPosition, wxSize( 50,20 ), 0 );
	txDataSizer3->Add( vyTextCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	vzLabel = new wxStaticText( this, wxID_ANY, wxT("z"), wxDefaultPosition, wxDefaultSize, 0 );
	vzLabel->Wrap( -1 );
	txDataSizer3->Add( vzLabel, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	vzTextCtrl = new wxTextCtrl( this, wxID_ANY, wxT("6.6"), wxDefaultPosition, wxSize( 50,20 ), 0 );
	txDataSizer3->Add( vzTextCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	accelerationLabel = new wxStaticText( this, wxID_ANY, wxT("Acceleration"), wxDefaultPosition, wxDefaultSize, 0 );
	accelerationLabel->Wrap( -1 );
	txDataSizer3->Add( accelerationLabel, 0, wxALIGN_CENTER|wxALL, 5 );
	
	axLabel = new wxStaticText( this, wxID_ANY, wxT("x"), wxDefaultPosition, wxDefaultSize, 0 );
	axLabel->Wrap( -1 );
	txDataSizer3->Add( axLabel, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	axTextCtrl = new wxTextCtrl( this, wxID_ANY, wxT("7.7"), wxDefaultPosition, wxSize( 50,20 ), 0 );
	txDataSizer3->Add( axTextCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	ayLabel = new wxStaticText( this, wxID_ANY, wxT("y"), wxDefaultPosition, wxDefaultSize, 0 );
	ayLabel->Wrap( -1 );
	txDataSizer3->Add( ayLabel, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	ayTextCtrl = new wxTextCtrl( this, wxID_ANY, wxT("8.8"), wxDefaultPosition, wxSize( 50,20 ), 0 );
	txDataSizer3->Add( ayTextCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	azLabel = new wxStaticText( this, wxID_ANY, wxT("z"), wxDefaultPosition, wxDefaultSize, 0 );
	azLabel->Wrap( -1 );
	txDataSizer3->Add( azLabel, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	azTextCtrl = new wxTextCtrl( this, wxID_ANY, wxT("9.9"), wxDefaultPosition, wxSize( 50,20 ), 0 );
	txDataSizer3->Add( azTextCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );
	
	txDataSizer->Add( txDataSizer3, 3, wxEXPAND, 5 );
	
	wxBoxSizer* txDataSizer4;
	txDataSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	txTextLabel = new wxStaticText( this, wxID_ANY, wxT("Text"), wxDefaultPosition, wxDefaultSize, 0 );
	txTextLabel->Wrap( -1 );
	txDataSizer4->Add( txTextLabel, 0, wxALIGN_CENTER|wxALL, 5 );
	
	txTextCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_NO_VSCROLL|wxTE_PROCESS_ENTER );
	txTextCtrl->Enable( false );
	
	txDataSizer4->Add( txTextCtrl, 1, wxALIGN_CENTER|wxALL|wxEXPAND, 5 );
	
	txDataSizer->Add( txDataSizer4, 1, wxEXPAND, 5 );
	
	txButton = new wxButton( this, wxID_ANY, wxT("Send"), wxDefaultPosition, wxDefaultSize, 0 );
	txButton->Enable( false );
	
	txDataSizer->Add( txButton, 0, wxALIGN_RIGHT|wxBOTTOM, 5 );
	
	txSizer->Add( txDataSizer, 4, wxEXPAND, 5 );
	
	panelSizer->Add( txSizer, 14, wxEXPAND|wxLEFT|wxRIGHT, 12 );
	
	wxStaticBoxSizer* connectionSizer;
	connectionSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Connection State") ), wxVERTICAL );
	
	wxFlexGridSizer* connectionFxSizer;
	connectionFxSizer = new wxFlexGridSizer( 1, 1, 0, 0 );
	connectionFxSizer->AddGrowableCol( 0 );
	connectionFxSizer->AddGrowableRow( 0 );
	connectionFxSizer->SetFlexibleDirection( wxBOTH );
	connectionFxSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	connectTextCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_NO_VSCROLL|wxTE_READONLY );
	connectionFxSizer->Add( connectTextCtrl, 0, wxALL|wxEXPAND, 10 );
	
	connectionSizer->Add( connectionFxSizer, 1, wxEXPAND, 5 );
	
	panelSizer->Add( connectionSizer, 10, wxALL|wxEXPAND, 12 );
	
	this->SetSizer( panelSizer );
	this->Layout();
	
	// Connect Events
	serverTextCtrl->Connect( wxEVT_CHAR, wxKeyEventHandler( MainPanel::onCharNumOnly ), NULL, this );
	serverTextCtrl->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainPanel::startStopMessenger ), NULL, this );
	startStopButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainPanel::startStopMessenger ), NULL, this );
	remoteHostTextCtrl->Connect( wxEVT_CHAR, wxKeyEventHandler( MainPanel::onCharIpAddr ), NULL, this );
	remotePortTextCtrl->Connect( wxEVT_CHAR, wxKeyEventHandler( MainPanel::onCharNumOnly ), NULL, this );
	timestampTextCtrl->Connect( wxEVT_CHAR, wxKeyEventHandler( MainPanel::onCharNumOnly ), NULL, this );
	seqNumTextCtrl->Connect( wxEVT_CHAR, wxKeyEventHandler( MainPanel::onCharNumOnly ), NULL, this );
	pxTextCtrl->Connect( wxEVT_CHAR, wxKeyEventHandler( MainPanel::onCharNumOnly ), NULL, this );
	pyTextCtrl->Connect( wxEVT_CHAR, wxKeyEventHandler( MainPanel::onCharNumOnly ), NULL, this );
	pzTextCtrl->Connect( wxEVT_CHAR, wxKeyEventHandler( MainPanel::onCharNumOnly ), NULL, this );
	vxTextCtrl->Connect( wxEVT_CHAR, wxKeyEventHandler( MainPanel::onCharNumOnly ), NULL, this );
	vyTextCtrl->Connect( wxEVT_CHAR, wxKeyEventHandler( MainPanel::onCharNumOnly ), NULL, this );
	vzTextCtrl->Connect( wxEVT_CHAR, wxKeyEventHandler( MainPanel::onCharNumOnly ), NULL, this );
	axTextCtrl->Connect( wxEVT_CHAR, wxKeyEventHandler( MainPanel::onCharNumOnly ), NULL, this );
	ayTextCtrl->Connect( wxEVT_CHAR, wxKeyEventHandler( MainPanel::onCharNumOnly ), NULL, this );
	azTextCtrl->Connect( wxEVT_CHAR, wxKeyEventHandler( MainPanel::onCharNumOnly ), NULL, this );
	txTextCtrl->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainPanel::sendMsg ), NULL, this );
	txButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainPanel::sendMsg ), NULL, this );

	// Hand done connection
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( MainPanel::onIdle ) );
}

MainPanel::~MainPanel()
{
	if(this->messenger != NULL)
		this->messenger->stop();
}

void MainPanel::startStopMessenger(wxCommandEvent& event)
{
	if(this->messenger == NULL || this->messenger->isRunning() != true)
	{
		int port = wxStringToInt(this->serverTextCtrl->GetValue().Trim());
		//this->messenger = boost::shared_ptr<Messenger>();
		this->messenger = boost::shared_ptr<Messenger>(new Messenger(port));
		this->messenger->start();
		this->startStopButton->SetLabel("Stop");
		this->txButton->Enable(true);
	}
	else
	{
		this->messenger->stop();
		this->startStopButton->SetLabel("Start");
		this->txButton->Enable(false);
	}
}

void MainPanel::sendMsg(wxCommandEvent& event)
{
	if(this->messenger != NULL && this->messenger->isRunning() == true)
	{
		wxString remoteHost = this->remoteHostTextCtrl->GetValue().Trim();
		int remotePort = wxStringToInt(this->remotePortTextCtrl->GetValue().Trim());
		
		Message msg = Message();
		msg.endpoint = udp::endpoint(boost::asio::ip::address::from_string(remoteHost.c_str()), remotePort);
		msg.data = this->getDataFromInterface();
		//this->messenger->sendMsg(msg);
		
		this->txTextCtrl->SetInsertionPoint(0);
		this->txTextCtrl->Clear();
		//this->txTextCtrl->SetFocus();
	}
}

void MainPanel::onIdle(wxIdleEvent& event)
{
	if(this->messenger != NULL && this->messenger->isRunning() == true)
	{
		//boost::shared_ptr<Message> msg = this->messenger->getNextRecvdMsg();
		//if(msg != NULL)
		{
			// ?
		}
	}
}

std::string MainPanel::getDataFromInterface()
{
	HeaderInformation header;
	this->getPacketInformation(header);

	std::vector<EntityInformation> entities;
	entities.push_back(EntityInformation());
	entities[0].stateInformationList.push_back(StateInformation());
	this->getDataFromTrackers(entities);

	return header.toString("\n") + entities[0].toString("\n");
}

void MainPanel::getPacketInformation(HeaderInformation& header)
{
	header.hostHandle = std::string(this->hostTextCtrl->GetValue().Trim().c_str());
	header.packetType = std::string(this->packetComboBox->GetValue().Trim().c_str());
	header.timestamp = wxStringToLong(this->timestampTextCtrl->GetValue().Trim());
	header.sequenceNumber = wxStringToInt(this->seqNumTextCtrl->GetValue().Trim());
}

void MainPanel::getDataFromTrackers(std::vector<EntityInformation>& entities)
{
	entities[0].handle = std::string(this->entityTextCtrl->GetValue().Trim().c_str());
	entities[0].stateInformationList[0].handle = std::string(this->stateTextCtrl->GetValue().Trim().c_str());
	entities[0].stateInformationList[0].position.x = wxStringToReal(this->pxTextCtrl->GetValue().Trim());
	entities[0].stateInformationList[0].position.y = wxStringToReal(this->pyTextCtrl->GetValue().Trim());
	entities[0].stateInformationList[0].position.z = wxStringToReal(this->pzTextCtrl->GetValue().Trim());
	entities[0].stateInformationList[0].velocity.x = wxStringToReal(this->vxTextCtrl->GetValue().Trim());
	entities[0].stateInformationList[0].velocity.y = wxStringToReal(this->vyTextCtrl->GetValue().Trim());
	entities[0].stateInformationList[0].velocity.z = wxStringToReal(this->vzTextCtrl->GetValue().Trim());
	entities[0].stateInformationList[0].acceleration.x = wxStringToReal(this->axTextCtrl->GetValue().Trim());
	entities[0].stateInformationList[0].acceleration.y = wxStringToReal(this->ayTextCtrl->GetValue().Trim());
	entities[0].stateInformationList[0].acceleration.z = wxStringToReal(this->azTextCtrl->GetValue().Trim());
}

void MainPanel::onCharNumOnly(wxKeyEvent& event)
{
	// TODO
	// Add code to filter the input characters
	event.Skip();
}

void MainPanel::onCharIpAddr(wxKeyEvent& event)
{
	// TODO
	// Add code to filter the input characters
	event.Skip();
}

