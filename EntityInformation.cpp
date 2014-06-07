#include "EntityInformation.h"
#include "StateInformation.h"
#include <sstream>
#include <iostream>
#include <boost/algorithm/string.hpp>

const std::string EntityInformation::HANDLE = "EntityHandle";

EntityInformation::EntityInformation() :
handle("-")
{

}

EntityInformation::EntityInformation(const std::string& data) :
handle("-")
{
	this->parseData(data);
}

std::string EntityInformation::toString(const std::string delimiter) const
{
	std::stringstream output;
	
	output << EntityInformation::HANDLE << ": " << this->handle << delimiter;
	std::vector<StateInformation>::const_iterator index;
	for(index = this->stateInformationList.begin(); index < this->stateInformationList.end(); ++index)
		output << index->toString(delimiter);
	
	return output.str();
}

void EntityInformation::parseData(const std::string& data)
{
	// Get rid of the old data
	this->stateInformationList.empty();

	// Split the data into seperate lines
	std::vector<std::string> lines;
	boost::split(lines, data, boost::is_any_of("\n"));

	// Parse remaining lines and extract state data
	if( lines.size() > StateInformation::LINES )
	{
		// Split first line into seperate tokens to get handle
		this->parseLine(lines[0], this->handle);
		std::string data;

		int i = 1;
		while(i < lines.size() - 1)
		{
			// Check to make sure not a new entity
			std::vector<std::string> tokens;
			splitLine(lines[i], tokens);
			if( tokens[0] != StateInformation::HANDLE )
				break;

			data = lines[i] + "\n" + lines[i+1] + "\n" + lines[i+2] + "\n" + lines[i+3] + "\n";

			//StateInformation newStateInfo = StateInformation(data);
			//this->stateInformationList.push_back(newStateInfo);
			this->stateInformationList.push_back(StateInformation(data));
			i += StateInformation::LINES;
		}
	}
}

