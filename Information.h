#ifndef INFORMATION_H
#define INFORMATION_H

/*
	|||||  Abstract Base Class
	|---------------------------------------------------------------------|
	|||||  Class Name:	Information
	|||||  By:			Fred Stakem
	|||||  Date:		1.14.09
*/

#include <string>
#include <vector>
#include "Vector3.h"

class Information
{
private:
	// Put member variables and functions here <>

public:
	// Destruction
	virtual ~Information(){}

	// Converts from data to string and from string to data
	virtual std::string toString(const std::string delimiter) const = 0;
	virtual void parseData(const std::string& data) = 0;

protected:
	// Line parsing functions
	void parseLine(const std::string& line, int& integer);
	void parseLine(const std::string& line, long& longInteger);
	void parseLine(const std::string& line, std::string& string);
	void parseLine(const std::string& line, Vector3& vector);
};

#endif