#ifndef HEADER_INFORMATION_H
#define HEADER_INFORMATION_H

/*
	|||||  Concrete Class
	|---------------------------------------------------------------------|
	|||||  Class Name:	Information - HeaderInformation
	|||||  By:			Fred Stakem
	|||||  Date:		1.14.09
*/

#include <string>
#include "Information.h"

class HeaderInformation : Information
{
private:
	// Put member variables and functions here <>

public:
	// Class variables
	static const int LINES = 4;
	static const std::string HOST_HANDLE;
	static const std::string PACKET_TYPE;
	static const std::string TIMESTAMP;
	static const std::string SEQUENCE_NUMBER;

	// Instance variable
	std::string hostHandle;
	std::string packetType;
	long timestamp;
	int sequenceNumber;

	// Creation and destruction
	HeaderInformation();
	HeaderInformation(const std::string& data);

	// Converts from data to string and from string to data
	std::string toString(const std::string delimiter) const;
	void parseData(const std::string& data);
};

#endif