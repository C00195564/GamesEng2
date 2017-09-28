#include "MacroCommand.h"

MacroCommand::MacroCommand()
{
	commands = new std::list<Command*>;
}

MacroCommand::~MacroCommand()
{

}

void MacroCommand::Add(Command* command)
{
	commands->push_back(command);
}

void MacroCommand::Remove(Command* command)
{
	commands->remove(command);
}

void MacroCommand::Clear()
{
	if (commands->size() != 0)
	{
		commands->clear();
	}
}

void MacroCommand::execute()
{//executes all commands in the list
	std::list<Command*>::iterator iter;
	for (iter = commands->begin(); iter != commands->end(); iter++)
	{
		(*iter)->execute();
	}

}

Command* MacroCommand::undo()
{
	if (commands->size() != 0)
	{
		Command* temp = commands->back();
		commands->back()->execute();
		auto iter = commands->end();
		iter--;
		commands->erase(iter);
		return temp;
	}
	else {
		return NULL;
	}
}