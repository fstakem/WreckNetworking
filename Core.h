#ifndef CORE_H
#define CORE_H

/*
	|||||  Core Data Types and Functions
	|---------------------------------------------------------------------|
	|||||  Class Name:	-
	|||||  By:			Fred Stakem
	|||||  Date:		12.17.09
*/
#define WIN32_LEAN_AND_MEAN 1

#include "math.h"
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>
#include "wx/wx.h"

#define real_sqrt sqrtf
typedef float real;

enum PacketTypes { Connect=0, Disconnect=1, StateUpdate=2, ConnectAck=3, DisconnectAck=4 };
const std::string PACKET_TYPES[] = { "Connect", "Disconnect", "StateUpdate", "ConnectAck", "DisconnectAck" };

void splitLine(const std::string &line, std::vector<std::string> &tokens);
int wxStringToInt(wxString value);
long wxStringToLong(wxString value);
real wxStringToReal(wxString value);



#endif