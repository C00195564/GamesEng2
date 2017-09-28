#include "command.h"
#include <iostream>

using namespace std;

class JumpCommand : public Command
{
public:
	virtual void execute() { 
		cout << "Jumping" << endl;
	}
	virtual Command* undo()
	{
		return NULL;
	}
};

class FireCommand : public Command
{
public:
	virtual void execute() { 
		cout << "Firing" << endl;
	}
	virtual Command* undo()
	{
		return NULL;
	}
};

class SwapCommand : public Command
{
public:
	virtual void execute() {
		cout << "Swapping weapon" << endl;
	}
	virtual Command* undo()
	{
		return NULL;
	}
};

class LurchCommand : public Command
{
public:
	virtual void execute() { 
		cout << "Lurching ineffectively" << endl;
	}
	virtual Command* undo()
	{
		return NULL;
	}
};