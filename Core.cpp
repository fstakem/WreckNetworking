#include "Core.h"

void splitLine(const std::string &line, std::vector<std::string> &tokens)
{
	// Split each line into seperate tokens
	boost::split(tokens, line, boost::is_any_of(":"));
	if(tokens.size() > 1)
		boost::trim(tokens[1]);
	else
	{
		tokens.push_back("error");
		tokens.push_back("error");
	}
}

int wxStringToInt(wxString value)
{
	int number;
	try
    {
		number = boost::lexical_cast<int>(value);
    }
	catch(boost::bad_lexical_cast &)
    {
		number = 10;
    }

	return number;
}

long wxStringToLong(wxString value)
{
	int number;
	try
    {
		number = boost::lexical_cast<long>(value);
    }
	catch(boost::bad_lexical_cast &)
    {
		number = 10;
    }

	return number;
}

real wxStringToReal(wxString value)
{
	real number;
	try
    {
		number = boost::lexical_cast<real>(value);
    }
	catch(boost::bad_lexical_cast &)
    {
		number = 10.0;
    }

	return number;
}