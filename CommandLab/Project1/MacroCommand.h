#include "command.h"
#include <list>
#include <iterator>

class MacroCommand : public Command {
public:
	MacroCommand();
	virtual ~MacroCommand();
	virtual void Add(Command* command);
	virtual void Clear();
	virtual void Remove(Command* command);
	virtual void MacroCommand::execute();
	virtual Command* undo();
	
private:
	std::list<Command*>* commands;
};