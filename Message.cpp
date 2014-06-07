#include "Message.h"
#include <iostream>
#include <sstream>
#include "Core.h"

const std::string Message::ENDPOINT = "Host";
const std::string Message::DATA = "Data";

Message::Message() :
endpoint(), data("")
{

}

Message::Message(const MessageContent& msgContent)
{
	this->setContent(msgContent);
}

std::string Message::toString(const std::string delimiter) const
{
	std::stringstream output;
		output << Message::ENDPOINT << "->  ip: " << this->endpoint.address() 
			   << "  port: " << this->endpoint.port() << std::endl
			   << this->data << delimiter;
		
	return output.str();
}

void Message::getContent(MessageContent& msgContent) const
{
	if(!this->data.empty())
	{
		// Split the data into seperate lines
		std::vector<std::string> lines;
		boost::split(lines, data, boost::is_any_of("\n"));

		std::vector<std::string>::const_iterator i = lines.begin();
		std::vector<std::string> tokens;
		std::stringstream stream;
		
		// Get the header information
		splitLine(*i, tokens);
		while(i != lines.end() || tokens[0] != EntityInformation::HANDLE)
		{
			stream << *i << std::endl;
			++i;
			splitLine(*i, tokens);
		}

		msgContent.header = HeaderInformation(stream.str());
		stream.str(std::string());

		// Get the body information
		while(i != lines.end())
		{
			stream << *i << std::endl;
			++i;
			splitLine(*i, tokens);
		
			while(i != lines.end() || tokens[0] != EntityInformation::HANDLE)
			{
				stream << *i << std::endl;
				++i;
				splitLine(*i, tokens);
			}

			msgContent.entities.push_back(EntityInformation(stream.str()));
			stream.str(std::string());
		}
	}
}

void Message::setContent(const MessageContent& msgContent)
{
	std::stringstream buffer;
	buffer << msgContent.header.toString("\n");

	std::vector<EntityInformation>::const_iterator i;
	for(i = msgContent.entities.begin(); i < msgContent.entities.end(); ++i)
	{
		buffer << i->toString("\n");	
	}

	this->data = buffer.str();
}