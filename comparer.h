#ifndef COMPARER
#define COMPARER

#include <iostream>
#include <string>
#include "contest_info.h"
#include "comp.h"


class unsigned_int_comparer
{
public:

	int comparate(unsigned int first, unsigned int second);

	~unsigned_int_comparer() = default;

};

class string_comparer {
public:

	int comparate(std::string first, std::string second);

	~string_comparer() = default;
};

class pair_int_comparer {

public:

	int comparate(std::pair<int, int> first, std::pair<int, int> second);

	~pair_int_comparer() = default;

};

class int_comparer {

public:

	int comparate(int first, int second);

	~int_comparer() = default;

};

class comparer_id_member_id_contest final : public comparer {

public:

	int comparate(contest_info* first, contest_info* second) override;

	/*int comparate(std::pair<int, int> first, contest_info* second);

	int comparate(contest_info* first, std::pair<int, int> second);*/

};

class comparer_resume final : public comparer {

public:

	int comparate(contest_info* first, contest_info* second) override;

	int comparate(std::string* first, contest_info* second);

	int comparate(contest_info* first, std::string* second);
};

class string_const_ptr {

public:

	int comparate(const std::string* first, const std::string* second);

	~string_const_ptr() = default;

};

#endif