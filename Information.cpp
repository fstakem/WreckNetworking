#include "Information.h"
#include "Core.h"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

void Information::parseLine(const std::string& line, int& integer)
{
	// Split first line into seperate tokens to get handle
	std::vector<std::string> tokens;
	splitLine(line, tokens);

	//Convert the strings to numbers
	try
    {
		integer = boost::lexical_cast<int>(tokens[1]);
    }
	catch(boost::bad_lexical_cast &)
    {
		integer = -1;
    }
}

void Information::parseLine(const std::string& line, long& longInteger)
{
	// Split first line into seperate tokens to get handle
	std::vector<std::string> tokens;
	splitLine(line, tokens);

	//Convert the strings to numbers
	try
    {
		longInteger = boost::lexical_cast<long>(tokens[1]);
    }
	catch(boost::bad_lexical_cast &)
    {
		longInteger = -1;
    }
}

void Information::parseLine(const std::string& line, std::string& string)
{
	// Split first line into seperate tokens to get handle
	std::vector<std::string> tokens;
	splitLine(line, tokens);
	string = std::string(tokens[1]);
}

void Information::parseLine(const std::string& line, Vector3& vector)
{
	// Split each line into seperate tokens
	std::vector<std::string> tokens;
	splitLine(line, tokens);
	std::vector<std::string> values;
	boost::split(values, tokens[1], boost::is_any_of(" "));

	//Convert the strings to numbers
	try
    {
		vector.x = boost::lexical_cast<real>(values[0]);
		vector.y = boost::lexical_cast<real>(values[1]);
		vector.z = boost::lexical_cast<real>(values[2]);
    }
	catch(boost::bad_lexical_cast &)
    {
		vector.x = 0.0;
		vector.y = 0.0;
		vector.z = 0.0;
    }
}
