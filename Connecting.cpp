#include "Connecting.h"

Connecting::Connecting(boost::shared_ptr<Session> session) :
State(session)
{
	
}

void Connecting::enter()
{

}

bool Connecting::rxMsg(const Message& rxMsg, Message& txMsg, std::vector<EntityInformation>& remoteState)
{
	this->parseMsg(rxMsg);

	if(this->msgContent.header.packetType.compare(PACKET_TYPES[Connect]) == 0)
	{
		// Remote user trying to connect
		// State -> simultaneous connection attempts
		// Action -> move to connection state
	}
	else if(this->msgContent.header.packetType.compare(PACKET_TYPES[Disconnect]) == 0)
	{
		// Remote user trying to disconnect
		// Error -> not connected
		// ??
	}
	else if(this->msgContent.header.packetType.compare(PACKET_TYPES[StateUpdate]) == 0)
	{
		// Remote user trying to update state
		// Error -> not connected
		// ??
	}
	else if(this->msgContent.header.packetType.compare(PACKET_TYPES[ConnectAck]) == 0)
	{
		// Remote user responding to connect
		// Action -> move to connection state
	}
	else if(this->msgContent.header.packetType.compare(PACKET_TYPES[DisconnectAck]) == 0)
	{
		// Remote user responding to disconnect
		// Error -> not connected
		// Action -> move to disconnection state
	}
	else
	{
		// Error -> msg not recognized
		// Action -> Do nothing
	}

	return true;
}

bool Connecting::txMsg(const std::vector<EntityInformation>& localState, Message& txMsg)
{
	return true;
}

void Connecting::exit()
{

}