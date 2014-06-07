#include "Disconnecting.h"

Disconnecting::Disconnecting(boost::shared_ptr<Session> session) :
State(session)
{
	
}

void Disconnecting::enter()
{

}

bool Disconnecting::rxMsg(const Message& rxMsg, Message& txMsg, std::vector<EntityInformation>& remoteState)
{
	this->parseMsg(rxMsg);

	if(this->msgContent.header.packetType.compare(PACKET_TYPES[Connect]) == 0)
	{
		// Remote user trying to connect
	}
	else if(this->msgContent.header.packetType.compare(PACKET_TYPES[Disconnect]) == 0)
	{
		// Remote user trying to disconnect
		// State -> simultaneous disconnection attempts
		// Action -> move to disconnection state
		this->respondDisconnectAck(txMsg);
	}
	else if(this->msgContent.header.packetType.compare(PACKET_TYPES[StateUpdate]) == 0)
	{
		// Remote user trying to update state
	}
	else if(this->msgContent.header.packetType.compare(PACKET_TYPES[ConnectAck]) == 0)
	{
		// Remote user responding to connect
	}
	else if(this->msgContent.header.packetType.compare(PACKET_TYPES[DisconnectAck]) == 0)
	{
		// Remote user responding to disconnect
	}	
	else
	{
		// Error -> msg not recognized
		// Action -> Do nothing
	}
	
	return true;
}

bool Disconnecting::txMsg(const std::vector<EntityInformation>& localState, Message& txMsg)
{
	return true;
}
	
void Disconnecting::exit()
{

}