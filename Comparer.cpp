#include "comparer.h"

int string_comparer::comparate(std::string first, std::string second)
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

int pair_int_comparer::comparate(std::pair<int, int> first, std::pair<int, int> second) {
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

int int_comparer::comparate(int first, int second) {
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

int unsigned_int_comparer::comparate(unsigned int first, unsigned int second) {
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

int comparer_id_member_id_contest::comparate(contest_info* first, contest_info* second) {
	if (first->get_id_member() > second->get_id_member()) {
		return 1;
	}
	else if (first->get_id_member() < second->get_id_member()) {
		return 2;
	}
	else {
		if (first->get_id_contest() > second->get_id_contest()) {
			return 1;
		}
		else if (first->get_id_contest() < second->get_id_contest()) {
			return 2;
		}
		else {
			return 0;
		}
	}
}

int comparer_id_member_id_contest::comparate(std::pair<int, int> first, contest_info* second) {
	if (first.first > second->get_id_member()) {
		return 1;
	}
	else if (first.first < second->get_id_member()) {
		return 2;
	}
	else {
		if (first.second > second->get_id_contest()) {
			return 1;
		}
		else if (first.second < second->get_id_contest()) {
			return 2;
		}
		else {
			return 0;
		}
	}
}

int comparer_id_member_id_contest::comparate(contest_info* first, std::pair<int, int> second) {
	if (first->get_id_member() > second.first) {
		return 1;
	}
	else if (first->get_id_member() < second.first) {
		return 2;
	}
	else {
		if (first->get_id_contest() > second.second) {
			return 1;
		}
		else if (first->get_id_contest() < second.second) {
			return 2;
		}
		else {
			return 0;
		}
	}
}