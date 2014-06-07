#include "Thread.h"

Thread::Thread() :
isThreadRunning(false), thread()
{

}

void Thread::start()
{
	this->isThreadRunning = true;
}

void Thread::stop()
{
	this->isThreadRunning = false;
}

bool Thread::isRunning()
{
	return this->isThreadRunning;
}
