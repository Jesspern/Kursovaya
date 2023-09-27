#ifndef COMPARER
#define COMPARER

#include <iostream>
#include <string>


class comparer
{
public:

	int comparate(int first, int second);
	int comparate(unsigned int first, unsigned int second);
	int comparate(std::string first, std::string second);
	int comparate(std::pair<int, int> first, std::pair<int, int> second);

};
#endif