#include "Messenger.h"
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include "wx/wx.h"

Messenger::Messenger(short port) :
ioService(), 
socket(udp::socket(ioService, udp::endpoint(udp::v4(), port)))
{
	std::stringstream debugStream;
	debugStream << "Messenger created. Listening on port: " << port;
	wxLogMessage(wxString(debugStream.str()));
}

Messenger::~Messenger()
{
	wxLogMessage(wxString("Messenger destroyed."));
}

void Messenger::start()
{
	wxLogMessage(wxString("Attempting to start the Messenger..."));

	Thread::start();
	this->socket.async_receive_from(boost::asio::buffer(this->receiveBuffer, Messenger::BUFFER_SIZE), 
									this->rxFromEndpoint,
									boost::bind(&Messenger::handleReceivedMsg, 
												this, boost::asio::placeholders::error, 
												boost::asio::placeholders::bytes_transferred));
	this->thread = boost::shared_ptr<boost::thread>(
						new boost::thread(boost::bind(&Messenger::run, this)));

	wxLogMessage(wxString("Messenger started."));
}

void Messenger::stop()
{
	wxLogMessage(wxString("Attempting to stop the Messenger..."));

	Thread::stop();
	this->ioService.stop();
	this->emptyMsgQueues();

	wxLogMessage(wxString("Messenger stopped."));
}

void Messenger::getNextRxMsgs(std::vector<boost::shared_ptr<Message>>& msgs)
{
	int i = Messenger::MSG_PROCESSED_PER_CYCLE;
	while(!this->receiveMsgBuffer.empty() && i > 0)
	{
		msgs.push_back(this->receiveMsgBuffer.front());
		this->receiveMsgBuffer.pop();
		--i;
	}
}

void Messenger::setNextTxMsg(boost::shared_ptr<Message> msg)
{
	this->transmitMsgBuffer.push(msg);
}

void Messenger::handleReceivedMsg(const boost::system::error_code& error, size_t bytesRecvd)
{
	if(!error && bytesRecvd > 0)
	{
		boost::shared_ptr<Message> msg = boost::shared_ptr<Message>(new Message());
		msg->data = std::string(this->receiveBuffer, bytesRecvd);
		msg->endpoint = udp::endpoint(this->rxFromEndpoint);
		this->receiveMsgBuffer.push(msg);

		std::stringstream debugStream;
		debugStream << "Message received: ->" << std::endl << msg->toString(" ");
		wxLogMessage(wxString(debugStream.str()));
	}
	
	this->socket.async_receive_from(boost::asio::buffer(this->receiveBuffer, Messenger::BUFFER_SIZE), 
									this->rxFromEndpoint, 
									boost::bind(&Messenger::handleReceivedMsg, 
												this, boost::asio::placeholders::error, 
												boost::asio::placeholders::bytes_transferred));
}

void Messenger::handleSentMsg(const boost::system::error_code& error, size_t bytesSent)
{
	if(!error && bytesSent > 0)
	{
		std::stringstream debugStream;
		debugStream << "Message sent: ->" << std::endl << std::string(this->transmitBuffer, bytesSent);
		wxLogMessage(wxString(debugStream.str()));
	}
}

void Messenger::emptyMsgQueues()
{
	while(!this->receiveMsgBuffer.empty())
	{
		this->receiveMsgBuffer.pop();
	}

	while(!this->transmitMsgBuffer.empty())
	{
		this->transmitMsgBuffer.pop();
	}
}

void Messenger::run()
{
	wxLogMessage(wxString("Boost asio service up and running."));

	this->ioService.run();

	wxLogMessage(wxString("Boost asio service has stopped."));
}

void Messenger::transmitMsgs()
{
	int i = Messenger::MSG_PROCESSED_PER_CYCLE;
	while(this->isThreadRunning && !this->transmitMsgBuffer.empty() && i > 0)
	{
		strcpy(this->transmitBuffer, this->transmitMsgBuffer.front()->data.c_str());
		this->txToEndpoint = udp::endpoint(this->transmitMsgBuffer.front()->endpoint);
		this->socket.async_send_to(boost::asio::buffer(this->transmitBuffer, strlen(this->transmitBuffer)), 
								   this->txToEndpoint, boost::bind(&Messenger::handleSentMsg, 
								   this, 
								   boost::asio::placeholders::error, 
								   boost::asio::placeholders::bytes_transferred));
		this->transmitMsgBuffer.pop();
		--i;
	}
}