#ifndef MESSENGER_H
#define MESSENGER_H

/*
	|||||  Concrete Class
	|---------------------------------------------------------------------|
	|||||  Class Name:	Thread - Messenger
	|||||  By:			Fred Stakem
	|||||  Date:		1.14.09
*/

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <queue>
#include "Thread.h"
#include "Message.h"

using boost::asio::ip::udp;

class Messenger : public Thread
{
private:
	// Class variables
	static const int BUFFER_SIZE = 1024;
	static const int MSG_PROCESSED_PER_CYCLE = 5;

	// Asio variables
	boost::asio::io_service ioService;
	udp::socket socket;

	// Buffer variables
	udp::endpoint rxFromEndpoint;
	udp::endpoint txToEndpoint;
	char receiveBuffer[Messenger::BUFFER_SIZE];
	char transmitBuffer[Messenger::BUFFER_SIZE];

	// Message variables
	std::queue<boost::shared_ptr<Message>> receiveMsgBuffer;
	std::queue<boost::shared_ptr<Message>> transmitMsgBuffer;

public:
	// Creation and destruction
	Messenger(short port);
	virtual ~Messenger();

	// Control of the lifecycle of the asio overrides Thread functions
	void start();
	void stop();

	// Interface to the messages
	//void sendMsg(const Message& msg);
	void getNextRxMsgs(std::vector<boost::shared_ptr<Message>>& msgs);
	void setNextTxMsg(boost::shared_ptr<Message> msg);

private:
	// Asio callbacks for when boost::asio functions finish
	void handleReceivedMsg(const boost::system::error_code& error, size_t bytesRecvd);
	void handleSentMsg(const boost::system::error_code& error, size_t bytesSent);
	
	// Main loop where asio is run on a seperate thread
	void run();

	// Utility functions
	void emptyMsgQueues();
	void transmitMsgs();
};

#endif