#include "HeaderInformation.h"
#include "StateInformation.h"
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "wx/wx.h"

const std::string HeaderInformation::HOST_HANDLE = "HostHandle";
const std::string HeaderInformation::PACKET_TYPE = "PacketType";
const std::string HeaderInformation::TIMESTAMP = "Timestamp";
const std::string HeaderInformation::SEQUENCE_NUMBER = "SequenceNumber";

HeaderInformation::HeaderInformation() :
hostHandle("-"), packetType("-"), timestamp(-1), sequenceNumber(-1)
{

}

HeaderInformation::HeaderInformation(const std::string& data) :
hostHandle("-"), packetType("-"), timestamp(-1), sequenceNumber(-1)
{
	this->parseData(data);
}

std::string HeaderInformation::toString(const std::string delimiter) const
{
	std::stringstream output;
	
	output << HeaderInformation::HOST_HANDLE << ": " << this->hostHandle << delimiter;
	output << HeaderInformation::PACKET_TYPE << ": " << this->packetType << delimiter;
	output << HeaderInformation::TIMESTAMP << ": " << this->timestamp << delimiter;
	output << HeaderInformation::SEQUENCE_NUMBER << ": " << this->sequenceNumber << delimiter;
	
	return output.str();
}

void HeaderInformation::parseData(const std::string& data)
{
	// Split the data into seperate lines
	std::vector<std::string> lines;
	boost::split(lines, data, boost::is_any_of("\n"));

	// Parse lines to get header information
	if( lines.size() >= HeaderInformation::LINES )
	{
		this->parseLine(lines[0], this->hostHandle);
		this->parseLine(lines[1], this->packetType);
		this->parseLine(lines[2], this->timestamp);
		this->parseLine(lines[3], this->sequenceNumber);
	}
}
