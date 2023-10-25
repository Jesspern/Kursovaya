#ifndef DIALOGUE_USER
#define DIALOGUE_USER

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include "readstring.h"
#include "DataBase.h"
#include "commands.h"
#include <chrono>
#include <ctime>
#include <time.h>
//#include <Windows.h>
#include <regex>
#include "stringpool.h"
#include "DataBaseSave.h"
#include <stdio.h>
#include <limits>

class dialogue {

public:

	void dialogue_user(int argc, char* argv[]);

	void commands_from_file(std::ifstream& file, data_base* d_base);

	bool check_save(data_base* d_base, data_base::flag flag_tree);

	~dialogue() = default;

};


#endif // !DIALOGUE_USER
