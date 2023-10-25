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
#include <Windows.h>
#include <regex>
#include "stringpool.h"
#include "Dialogue_with_user.h"
#include "DataBaseSave.h"


int main(int argc, char* argv[]) {

	dialogue dl;

	try {
		dl.dialogue_user(argc, argv);
	}
	catch (std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}