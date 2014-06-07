#ifndef ENTITY_INFORMATION_H
#define ENTITY_INFORMATION_H

/*
	|||||  Concrete Class
	|---------------------------------------------------------------------|
	|||||  Class Name:	Information - EntityInformation
	|||||  By:			Fred Stakem
	|||||  Date:		1.14.09
*/

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "Information.h"
#include "StateInformation.h"

class EntityInformation : Information
{
private:
	// Put member variables and functions here <>

public:
	// Class variables
	static const int LINES = 1;
	static const std::string HANDLE;

	// Instance variable
	std::string handle;
	std::vector<StateInformation> stateInformationList;

	// Creation and destruction
	EntityInformation();
	EntityInformation(const std::string& data);

	// Converts from data to string and from string to data
	std::string toString(const std::string delimiter) const;
	void parseData(const std::string& data);
};

#endif