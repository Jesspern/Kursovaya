#ifndef READ_STRING
#define READ_STRING

#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>

class read_string {

public:

	int in_str(std::string* str, char* c, std::ifstream& file);

	int in_str_int(std::string* str, char* c, std::ifstream& file);

	int in_str_str(std::string* str, char* c, std::ifstream& file);

};
#endif