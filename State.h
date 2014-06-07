#ifndef STATE_H
#define STATE_H

/*
	|||||  Abstract Base Class
	|---------------------------------------------------------------------|
	|||||  Class Name:	State
	|||||  By:			Fred Stakem
	|||||  Date:		1.20.09
*/

#include "Core.h"
#include <vector>
#include <boost/shared_ptr.hpp>
#include "EntityInformation.h"
#include "Message.h"
#include "Session.h"

class Session;

class State
{
private:
	// Put member variables and functions here <>

public:
	State(boost::shared_ptr<Session> session);
	virtual ~State(){}

	// This will execute when the state is entered
	virtual void enter()=0;

	// This is the state's normal update function
	virtual bool rxMsg(const Message& rxMsg, Message& txMsg, std::vector<EntityInformation>& remoteState)=0;
	virtual bool txMsg(const std::vector<EntityInformation>& localState, Message& txMsg)=0;
	//virtual void update(const std::vector<EntityInformation>& localState, const Message& rxMsg,
						//std::vector<EntityInformation>& remoteState, Message& txMsg)=0;

	// This will execute when the state is exited
	virtual void exit()=0;

protected:
	// Ownders handle
	boost::shared_ptr<Session> session;

	// Helper functions
	void parseMsg(const Message& msg);
	void respondConnectAck(Message& msg);
	void respondDisconnectAck(Message& msg);

	// Data
	MessageContent msgContent;
};

#endif