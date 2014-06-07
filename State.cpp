#include "State.h"
#include "HeaderInformation.h"
#include <time.h>
#include "Connected.h"
#include "Disconnected.h"

State::State(boost::shared_ptr<Session> session) :
session(session)
{

}

void State::parseMsg(const Message& msg)
{
	msg.getContent(this->msgContent);
}

void State::respondConnectAck(Message& msg)
{
	MessageContent msgContent;
	msgContent.header.hostHandle = this->session->hostHandle;
	msgContent.header.packetType = PACKET_TYPES[ConnectAck];
	msgContent.header.sequenceNumber = this->session->getSequenceNumber(true);
	msgContent.header.timestamp = time(NULL);
	msg.setContent(msgContent);
}

void State::respondDisconnectAck(Message& msg)
{
	MessageContent msgContent;
	msgContent.header.hostHandle = this->session->hostHandle;
	msgContent.header.packetType = PACKET_TYPES[DisconnectAck];
	msgContent.header.sequenceNumber = this->session->getSequenceNumber(true);
	msgContent.header.timestamp = time(NULL);
	msg.setContent(msgContent);
}
