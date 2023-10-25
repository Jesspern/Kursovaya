#ifndef STRINGPOOL
#define STRINGPOOL

#include <iostream>
#include <vector>

class string_pool {

private:

	static string_pool* _instance;

	std::vector<std::string*> str_pool;

protected:

	string_pool() = default;

public:

	static string_pool* Instance();

	std::string* get_str(std::string const& str);

};

#endif