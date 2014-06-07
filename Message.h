#ifndef MESSAGE_H
#define MESSAGE_H

/*
	|||||  Concrete Class
	|---------------------------------------------------------------------|
	|||||  Class Name:	Message
	|||||  By:			Fred Stakem
	|||||  Date:		1.14.09
*/

#include <iostream>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include "HeaderInformation.h"
#include "EntityInformation.h"

using boost::asio::ip::udp;

struct MessageContent
{
	HeaderInformation header;
	std::vector<EntityInformation> entities;

	MessageContent()
	{
		header = HeaderInformation();
	}
};

class Message
{
private:
	// Put member variables and functions here <>

public:
	// Class variables
	static const std::string ENDPOINT;
	static const std::string DATA;

	// Instance variables
	udp::endpoint endpoint;
	std::string data;

	// Creation and destruction
	Message();
	Message(const MessageContent& msgContens);
	virtual ~Message(){}

	// Get the message data in different forms
	std::string toString(const std::string delimiter) const;
	void getContent(MessageContent& msgContent) const;
	void setContent(const MessageContent& msgContent);
};
#endif