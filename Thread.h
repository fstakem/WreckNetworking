#ifndef THREAD_H
#define THREAD_H

/*
	|||||  Abstract Base Class
	|---------------------------------------------------------------------|
	|||||  Class Name:	Thread
	|||||  By:			Fred Stakem
	|||||  Date:		1.14.09
*/

#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>

class Thread
{
private:
	// Put member variables and functions here <>

public:
	// Creation and destruction
	Thread();
	virtual ~Thread(){}

	// Public interface
	void start();
	void stop();
	bool isRunning();

protected:
	volatile bool isThreadRunning;
	boost::shared_ptr<boost::thread> thread;
	boost::mutex mutex;

	// Subclasses must implement this
	virtual void run() = 0;
};

#endif