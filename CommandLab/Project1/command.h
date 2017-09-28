
class Command
{
public:
	virtual ~Command() {}
	virtual void execute() = 0;
	virtual Command* undo() = 0;

protected:
	Command() {}
};