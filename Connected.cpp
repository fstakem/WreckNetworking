#include "Connected.h"

Connected::Connected(boost::shared_ptr<Session> session) :
State(session)
{
	
}

void Connected::enter()
{

}

bool Connected::rxMsg(const Message& rxMsg, Message& txMsg, std::vector<EntityInformation>& remoteState)
{
	this->parseMsg(rxMsg);

	if(this->msgContent.header.packetType.compare(PACKET_TYPES[Connect]) == 0)
	{
		// Remote user trying to connect
		// Error -> already connected
		// Action -> respond to insure both ends connected
		this->respondConnectAck(txMsg);
	}
	else if(this->msgContent.header.packetType.compare(PACKET_TYPES[Disconnect]) == 0)
	{
		// Remote user trying to disconnect
		// Action -> move to disconnected state
		this->respondDisconnectAck(txMsg);
	}
	else if(this->msgContent.header.packetType.compare(PACKET_TYPES[StateUpdate]) == 0)
	{
		// Remote user trying to update state
		// Action -> process data
	}
	else if(this->msgContent.header.packetType.compare(PACKET_TYPES[ConnectAck]) == 0)
	{
		// Remote user responding to connect
		// Error -> already connected
		// Action -> Do nothing
	}
	else if(this->msgContent.header.packetType.compare(PACKET_TYPES[DisconnectAck]) == 0)
	{
		// Remote user responding to disconnect
		// Error -> local user not trying to disconnect
		// Action -> disconnect anyway
	}
	else
	{
		// Error -> msg not recognized
		// Action -> Do nothing
	}

	// temp
	return true;
}

bool Connected::txMsg(const std::vector<EntityInformation>& localState, Message& txMsg)
{
	return true;
}

void Connected::exit()
{

}