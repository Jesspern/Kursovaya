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

int read_string::in_data_str(std::string* str, char* c, std::ifstream& file) {
	file >> std::noskipws >> (*c);
	if (isdigit(*c) == 0) {
		return 3;
	}
	(*str).append(1, (*c));
	file >> std::noskipws >> (*c);
	if (isdigit(*c) == 0) {
		return 3;
	}
	(*str).append(1, (*c));
	file >> std::noskipws >> (*c);
	if ((*c) != ' ') {
		return 3;
	}
	file >> std::noskipws >> (*c);
	if (isdigit(*c) == 0) {
		return 3;
	}
	(*str).append(1, (*c));
	file >> std::noskipws >> (*c);
	if (isdigit(*c) == 0) {
		return 3;
	}
	(*str).append(1, (*c));
	file >> std::noskipws >> (*c);
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

void read_string::in_data(std::string str, int* data) {
	if (str[0] != '0' and str[0] != '1') {
		if (str[0] == '2') {
			if (str[1] > '3' and str[1] < '0') {
				throw std::invalid_argument("Data is not correct");
			}
		}
		else {
			throw std::invalid_argument("Data is not correct");
		}
		if (str[2] > '5' or str[2] < '0') {
			throw std::invalid_argument("Data is not correct");
		}
		(*data) = std::stoi(str);
		return;
	}
	else {
		if (str[2] > '5' or str[2] < '0') {
			throw std::invalid_argument("Data is not correct");
		}
		(*data) = std::stoi(str);
		return;
	}

}


int read_string::in_hour_str(int* seconds, char* c, std::ifstream& file) {
	std::string str;
	file >> std::noskipws >> (*c);
	if (isdigit(*c) == 0) {
		return 3;
	}
	str.append(1, *c);
	file >> std::noskipws >> (*c);
	if (isdigit(*c) == 0) {
		return 3;
	}
	str.append(1, *c);
	if (str[0] != '0' and str[0] != '1') {
		if (str[0] == '2') {
			if (str[1] > '3' and str[1] < '0') {
				return 3;
			}
		}
		else {
			return 3;
		}
		*seconds = (std::stoi(str) * 3600);
	}
	file >> std::noskipws >> (*c);
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

int read_string::in_minute_str(int* seconds, char* c, std::ifstream& file) {
	std::string str;
	file >> std::noskipws >> (*c);
	if (isdigit(*c) == 0) {
		return 3;
	}
	str.append(1, *c);
	file >> std::noskipws >> (*c);
	if (isdigit(*c) == 0) {
		return 3;
	}
	str.append(1, *c);
	if (str[0] > '5' or str[0] < '0') {
		return 3;
	}
	*seconds = (std::stoi(str) * 60);
	file >> std::noskipws >> (*c);
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

int read_string::in_seconds_str(int* seconds, char* c, std::ifstream& file) {
	std::string str;
	file >> std::noskipws >> (*c);
	if (isdigit(*c) == 0) {
		return 3;
	}
	str.append(1, *c);
	file >> std::noskipws >> (*c);
	if (isdigit(*c) == 0) {
		return 3;
	}
	str.append(1, *c);
	if (str[0] > '5' or str[0] < '0') {
		return 3;
	}
	*seconds = (std::stoi(str));
	file >> std::noskipws >> (*c);
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