#ifndef COMMAND
#define COMMAND

#include <ctime>

class contest_info;

class command {

public:

	command* next_command = nullptr;
	time_t _time;

	virtual void execute() = 0;

	virtual void execute(contest_info& command) = 0;

	virtual ~command() = default;

};

#endif // !COMMAND