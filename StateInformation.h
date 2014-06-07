#ifndef STATE_INFORMATION_H
#define STATE_INFORMATION_H

/*
	|||||  Concrete Class
	|---------------------------------------------------------------------|
	|||||  Class Name:	Information - StateInformation
	|||||  By:			Fred Stakem
	|||||  Date:		1.14.09
*/

#include <string>
#include <vector>
#include "Core.h"
#include "Vector3.h"
#include "Information.h"

class StateInformation : Information
{
private:
	// Put member variables and functions here <>

public:
	// Class variables
	static const int LINES = 4;
	static const std::string HANDLE;
	static const std::string POSITION;
	static const std::string VELOCITY;
	static const std::string ACCELERATION;

	// Instance variable
	std::string handle;
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;

	// Creation and destruction
	StateInformation();
	StateInformation(const std::string& data);
	
	// Converts from data to string and from string to data
	std::string toString(const std::string delimiter) const;
	void parseData(const std::string& data);
};

#endif