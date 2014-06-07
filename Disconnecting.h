#ifndef DISCONNECTING_H
#define DISCONNECTING_H

/*
	|||||  Concrete Class
	|---------------------------------------------------------------------|
	|||||  Class Name:	State - Disconnecting
	|||||  By:			Fred Stakem
	|||||  Date:		1.20.09
*/

#include "Core.h"
#include "State.h"

class Disconnecting : public State
{
private:
	// Put member variables and functions here <>

public:
	// Creation and destruction
	Disconnecting(boost::shared_ptr<Session> session);

	// State events
	virtual void enter();
	virtual bool rxMsg(const Message& rxMsg, Message& txMsg, std::vector<EntityInformation>& remoteState);
	virtual bool txMsg(const std::vector<EntityInformation>& localState, Message& txMsg);
	virtual void exit();
};

#endif