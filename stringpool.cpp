#include "stringpool.h"

std::string* string_pool::get_str(std::string str) {
	return &str;
}