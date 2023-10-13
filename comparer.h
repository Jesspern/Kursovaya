#ifndef COMPARER
#define COMPARER

#include <iostream>
#include <string>
#include "contest_info.h"


class unsigned_int_comparer
{
public:

	int comparate(unsigned int first, unsigned int second);

};

class string_comparer {
public:

	int comparate(std::string first, std::string second);
};

class pair_int_comparer {

public:

	int comparate(std::pair<int, int> first, std::pair<int, int> second);

};

class int_comparer {

public:

	int comparate(int first, int second);

};

class comparer_id_member_id_contest {

public:

	int comparate(contest_info* first, contest_info* second);

	int comparate(std::pair<int, int> first, contest_info* second);

	int comparate(contest_info* first, std::pair<int, int> second);
};
#endif