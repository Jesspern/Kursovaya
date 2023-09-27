#include "readstring.h"

int read_string::in_str(std::string* str, char* c, std::ifstream& file) {
	file >> std::noskipws >> (*c);
	if ((*c) != ' ' or (!file.eof()) or (*c) != '\n') {
		(*str).append(1, (*c));
	}
	if ((*c) == EOF) {
		return 1;
	}
	while ((*c) != ' ' and (!file.eof()) and (*c) != '\n') {
		file >> std::noskipws >> (*c);
		if ((*c) == ' ' or file.eof() or (*c) == '\n') {
			break;
		}
		(*str).append(1, *c);
	}
	if ((*c) == ' ') {
		return 0;
	}
	if (file.eof()) {
		return 1;
	}
	if ((*c) == '\n') {
		return 2;
	}
	return 3;
}

int read_string::in_str_int(std::string* str, char* c, std::ifstream& file) {
	file >> std::noskipws >> (*c);
	if (isdigit(*c) == 0) {
		return 3;
	}
	if ((*c) != ' ' or (!file.eof()) or (*c) != '\n') {
		(*str).append(1, (*c));
	}
	if (file.eof()) {
		return 1;
	}
	while ((*c) != ' ' and (!file.eof()) and (*c) != '\n') {
		file >> std::noskipws >> (*c);
		if ((*c) == ' ' or file.eof() or (*c) == '\n') {
			break;
		}
		if (isdigit(*c) == 0) {
			return 3;
		}
		(*str).append(1, *c);
	}
	if ((*c) == ' ') {
		return 0;
	}
	if (file.eof()) {
		return 1;
	}
	if ((*c) == '\n') {
		return 2;
	}
	return 3;
}

int read_string::in_str_str(std::string* str, char* c, std::ifstream& file) {
	file >> std::noskipws >> (*c);
	if (isalpha(*c) == 0) {
		return 3;
	}
	if ((*c) != ' ' or (!file.eof()) or (*c) != '\n') {
		(*str).append(1, (*c));
	}
	if (file.eof()) {
		return 1;
	}
	while ((*c) != ' ' and (!file.eof()) and (*c) != '\n') {
		file >> std::noskipws >> (*c);
		if ((*c) == ' ' or file.eof() or (*c) == '\n') {
			break;
		}
		if (isalpha(*c) == 0) {
			return 3;
		}
		(*str).append(1, *c);
	}
	if ((*c) == ' ') {
		return 0;
	}
	if (file.eof()) {
		return 1;
	}
	if ((*c) == '\n') {
		return 2;
	}
	return 3;
}
