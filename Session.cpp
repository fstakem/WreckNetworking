#include "Session.h"
#include "Disconnected.h"

Session::Session() :
currentState(boost::shared_ptr<State>(new Disconnected(boost::shared_ptr<Session>(this)))),
localSeqNumber(1), remoteSeqNumber(1)
{

}

/*
void Session::setCurrentState(boost::shared_ptr<State> state)
{
	this->currentState = state;
}
*/

int Session::getSequenceNumber(bool local)
{
	if(local)
		return this->localSeqNumber++;
	else
		return this->remoteSeqNumber++;
}

boost::shared_ptr<State> Session::getCurrentState() const
{
	return this->currentState;
}

void Session::changeState(boost::shared_ptr<State> newState)
{
	// Call the exit method of the last state
	this->currentState->exit();

	// Change state to the new state
	this->currentState = newState;

	// Call the entry method of the new state
	this->currentState->enter();
}

void Session::update(const std::vector<EntityInformation>& localState, const Message& rxMsg,
					 std::vector<EntityInformation>& remoteState, Message& txMsg)
{
	
}

bool Session::isInState(const boost::shared_ptr<State> state) const
{
		return typeid(*this->currentState) == typeid(state);
}

bool Session::isHost(std::string ip, short port)
{
	if(this->ip.compare(ip) == 0 && this->port == port)
		return true;
	else
		return false;
}