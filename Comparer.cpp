#include "comparer.h"

int comparer::comparate(int first, int second)
{
	if (first > second) {
		return 1;
	}
	else if (first < second) {
		return 2;
	}
	else {
		return 0;
	}
}

int comparer::comparate(unsigned int first, unsigned int second)
{
	if (first > second) {
		return 1;
	}
	else if (first < second) {
		return 2;
	}
	else {
		return 0;
	}
}

int comparer::comparate(std::string first, std::string second)
{
	int res = first.compare(second);
	if (res > 0) {
		return 1;
	}
	else if (res < 0) {
		return 2;
	}
	else {
		return 0;
	}
}

int comparer::comparate(std::pair<int, int> first, std::pair<int, int> second)
{
	if (first.first > second.first) {
		return 1;
	}
	else if (first.first < second.first) {
		return 2;
	}
	else {
		if (first.second > second.second) {
			return 1;
		}
		else if (first.second < second.second) {
			return 2;
		}
		else {
			return 0;
		}
	}
}