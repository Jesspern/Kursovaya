#ifndef DIALOGUE_USER
#define DIALOGUE_USER

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include "readstring.h"
//#include "DataBase.h"
//#include "commands.h"
#include <chrono>
#include <ctime>
#include <time.h>
#include <Windows.h>
#include <regex>
#include "stringpool.h"


class dialogue {

public:

	void dialogue_user(int argc, char* argv[]);

	~dialogue() = default;

};


#endif // !DIALOGUE_USER
