#include "Disconnected.h"

Disconnected::Disconnected(boost::shared_ptr<Session> session) :
State(session)
{
	
}

void Disconnected::enter()
{

}

bool Disconnected::rxMsg(const Message& rxMsg, Message& txMsg, std::vector<EntityInformation>& remoteState)
{
	this->parseMsg(rxMsg);

	if(this->msgContent.header.packetType.compare(PACKET_TYPES[Connect]) == 0)
	{
		// Remote user trying to connect
		// Action -> move to connection state
		this->respondConnectAck(txMsg);
	}
	else if(this->msgContent.header.packetType.compare(PACKET_TYPES[Disconnect]) == 0)
	{
		// Remote user trying to disconnect
		// Error -> not connected 
		// Action -> respond to insure both ends disconnected
		this->respondDisconnectAck(txMsg);
	}
	else if(this->msgContent.header.packetType.compare(PACKET_TYPES[StateUpdate]) == 0)
	{
		// Remote user trying to update state
		// Error -> not connected
		// Action -> respond to insure both ends disconnected
		this->respondDisconnectAck(txMsg);
	}
	else if(this->msgContent.header.packetType.compare(PACKET_TYPES[ConnectAck]) == 0)
	{
		// Remote user responding to connect
		// Error -> not trying to connect
		// Action -> respond to insure both ends disconnected
		this->respondDisconnectAck(txMsg);
	}
	else if(this->msgContent.header.packetType.compare(PACKET_TYPES[DisconnectAck]) == 0)
	{
		// Remote user responding to disconnect
		// Error -> not connected
		// Action -> Do nothing
	}
	else
	{
		// Remote user send unknown message
		// Error -> msg not recognized
		// Action -> Do nothing
	}

	return true;
}

bool Disconnected::txMsg(const std::vector<EntityInformation>& localState, Message& txMsg)
{
	return true;
}

void Disconnected::exit()
{

}