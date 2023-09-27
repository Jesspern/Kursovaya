#include "contest_info.h"

contest_info::contest_info(unsigned int id_member, std::string name, std::string surname,
	std::string patronymic, std::string day_of_birthday, std::string resume,
	unsigned int id_hrmanager, unsigned int id_contest, std::string prog_lang,
	unsigned int tasks_count, unsigned int tasks_complete, bool cheating) {
		
	_id_member = id_member;
	_name = name;
	_surname = surname;
	_patronymic = patronymic;
	_day_of_birthday = day_of_birthday;
	_resume = resume;
	_id_hrmanager = id_hrmanager;
	_id_contest = id_contest;
	_prog_lang = prog_lang;
	_tasks_count = tasks_count;
	_tasks_complete = tasks_complete;
	_cheating = cheating;

}

void contest_info::set_id_member(unsigned int id_member) {
	_id_member = id_member;
}

unsigned int contest_info::get_id_member() const {
	return _id_member;
}

void contest_info::set_name(std::string const & name) {
	_name = name;
}

std::string contest_info::get_name() const {
	return _name;
}

void contest_info::set_surname(std::string surname) {
	_surname = surname;
}

std::string contest_info::get_surname() const {
	return _surname;
}

void contest_info::set_patronymic(std::string patronymic) {
	_patronymic = patronymic;
}

std::string contest_info::get_patronymic() const {
	return _patronymic;
}

void contest_info::set_day_of_birthday(std::string day_of_birthday) {
	_day_of_birthday = day_of_birthday;
}

std::string contest_info::get_day_of_birthday() const {
	return _day_of_birthday;
}

void contest_info::set_resume(std::string resume) {
	_resume = resume;
}

std::string contest_info::get_resume() const {
	return _resume;
}

void contest_info::set_id_hrmanager(unsigned int id_hrmanager) {
	_id_hrmanager = id_hrmanager;
}

unsigned int contest_info::get_id_hrmanager() const {
	return _id_hrmanager;
}

void contest_info::set_id_contest(unsigned int id_contest) {
	_id_contest = id_contest;
}

unsigned int contest_info::get_id_contest() const {
	return _id_contest;
}

void contest_info::set_prog_lang(std::string prog_lang) {
	_prog_lang = prog_lang;
}

std::string contest_info::get_prog_lang() const {
	return _prog_lang;
}

void contest_info::set_tasks_count(unsigned int tasks_count) {
	_tasks_count = tasks_count;
}

unsigned int contest_info::get_tasks_count() const {
	return _tasks_count;
}

void contest_info::set_tasks_complete(unsigned int tasks_complete) {
	_tasks_complete = tasks_complete;
}

unsigned int contest_info::get_tasks_complete() const {
	return _tasks_complete;
}

void contest_info::set_cheating(bool cheating) {
	_cheating = cheating;
}

bool contest_info::get_cheating() const {
	return _cheating;
}

std::ostream& operator << (std::ostream& os, const contest_info& info) {
	os << "ID member:  " << info._id_member << std::endl;
	os << "Full name: " << info._name << " " << info._surname << " " << info._patronymic << " " << std::endl;
	os << "Day of Birthday: " << info._day_of_birthday << std::endl;
	os << "Summary link: " << info._resume << std::endl;
	os << "ID HR manager: " << info._id_hrmanager << std::endl;
	os << "ID contest: " << info._id_contest << std::endl;
	os << "Programming language: " << info._prog_lang << std::endl;
	os << "Number of tasks: " << info._tasks_count << std::endl
		<< "Tasks complete: " << info._tasks_complete << std::endl;
	if (info._cheating) {
		os << "Cheating" << std::endl;
	}
	else {
		os << "Don't cheating" << std::endl;
	}

	return os;
}