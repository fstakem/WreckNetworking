#ifndef SESSION_H
#define SESSION_H

/*
	|||||  Concrete Class
	|---------------------------------------------------------------------|
	|||||  Class Name:	Session
	|||||  By:			Fred Stakem
	|||||  Date:		1.20.09
*/

#include <boost/shared_ptr.hpp>
#include "State.h"

class State;

class Session
{
private:
	// Current state of session
	boost::shared_ptr<State> currentState;

	// Remote host associated with the session
	std::string ip;
	short port;

	// Sequence numbers for session
	int localSeqNumber;
	int remoteSeqNumber;
	
public:
	Session();
	virtual ~Session(){}

	// Not sure what to do with yet???
	std::string hostHandle;

	// Handle for packet sequence numbers
	int getSequenceNumber(bool local);
	
	// Get, set, and change the current state
	//void setCurrentState(boost::shared_ptr<State> state);
	boost::shared_ptr<State> getCurrentState() const;
	void changeState(boost::shared_ptr<State> newState);

	// Control states
	void connect(std::string ip, short port);
	void disconnect();
	void update(const std::vector<EntityInformation>& localState, const Message& rxMsg,
				std::vector<EntityInformation>& remoteState, Message& txMsg);
	
	// Queries
	bool isInState(const boost::shared_ptr<State> state) const;
	bool isHost(std::string ip, short port);
};

#endif


