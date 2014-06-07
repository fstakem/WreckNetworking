#include "StateInformation.h"
#include <sstream>
#include <vector>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>

const std::string StateInformation::HANDLE = "StateHandle";
const std::string StateInformation::POSITION = "Position";
const std::string StateInformation::VELOCITY = "Velocity";
const std::string StateInformation::ACCELERATION = "Acceleration";

StateInformation::StateInformation() :
handle("-"), 
position(Vector3()), 
velocity(Vector3()), 
acceleration(Vector3())
{

}

StateInformation::StateInformation(const std::string& data) :
handle("-"), 
position(Vector3()), 
velocity(Vector3()), 
acceleration(Vector3())
{
	this->parseData(data);
}

std::string StateInformation::toString(const std::string delimiter) const
{
	std::stringstream output;
	
	output << StateInformation::HANDLE << ": " << this->handle << delimiter;
	output << StateInformation::POSITION << ": " << this->position.toString() << delimiter;
	output << StateInformation::VELOCITY << ": " << this->velocity.toString() << delimiter;
	output << StateInformation::ACCELERATION << ": " << this->acceleration.toString() << delimiter;
	
	return output.str();
}

void StateInformation::parseData(const std::string& data)
{
	// Split the data into seperate lines
	std::vector<std::string> lines;
	boost::split(lines, data, boost::is_any_of("\n"));

	if( lines.size() >= 4)
	{
		// Split first line into seperate tokens to get handle
		this->parseLine(lines[0], this->handle);

		// Parse remaining lines and extract state data
		this->parseLine(lines[1], this->position);
		this->parseLine(lines[2], this->velocity);
		this->parseLine(lines[3], this->acceleration);
	}
}
