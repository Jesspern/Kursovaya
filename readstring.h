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

	int in_data_str(std::string* str, char* c, std::ifstream& file);

	int in_hour_str(int* seconds, char* c, std::ifstream& file);

	int in_minute_str(int* seconds, char* c, std::ifstream& file);

	int in_seconds_str(int* seconds, char* c, std::ifstream& file);

	void in_data(std::string str, int* data);

	int read_data(std::string* str, char* c, std::ifstream& file);

	~read_string() = default;

};
#endif