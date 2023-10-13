#ifndef STRINGPOOL
#define STRINGPOOL

#include <iostream>
#include <list>

class string_pool {

private:

	std::list<std::string> str_pool;

public:

	std::string* get_str(std::string str);

};

#endif