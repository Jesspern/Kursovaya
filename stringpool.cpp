#include "stringpool.h"

string_pool* string_pool::_instance = 0;

string_pool* string_pool::Instance() {
	if (_instance == 0) {
		_instance = new string_pool;
	}
	return _instance;
}

std::string* string_pool::get_str(std::string const& str) {
	std::string* element = new std::string(str);
	if (str_pool.empty()) {
		str_pool.push_back(element);
		return (str_pool.front());
	}
	else {
		for (auto str_it = str_pool.begin(); str_it != str_pool.end(); str_it++) {
			if (str == *(*str_it)) {
				return (*str_it);
			}
		}
		str_pool.push_back(element);
		return (str_pool.back());
	}
}