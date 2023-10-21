#include "contest_info.h"

contest_info::contest_info(int id_member, const std::string* name, const std::string* surname,
	const std::string* patronymic, const std::string* day_of_birthday, const std::string* resume,
	int id_hrmanager, int id_contest, const std::string* prog_lang, int tasks_count, 
	int tasks_complete, bool cheating) {
		
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

contest_info& contest_info::operator=(const contest_info& other) {
	this->set_id_member(other.get_id_member());
	this->set_name(other.get_name());
	this->set_surname(other.get_surname());
	this->set_patronymic(other.get_patronymic());
	this->set_day_of_birthday(other.get_day_of_birthday());
	this->set_resume(other.get_resume());
	this->set_id_hrmanager(other.get_id_hrmanager());
	this->set_id_contest(other.get_id_contest());
	this->set_prog_lang(other.get_prog_lang());
	this->set_tasks_count(other.get_tasks_count());
	this->set_tasks_complete(other.get_tasks_complete());
	this->set_cheating(other.get_cheating());
	return *this;
}

void contest_info::set_id_member(int id_member) {
	_id_member = id_member;
}

int contest_info::get_id_member() const {
	return _id_member;
}

void contest_info::set_name(const std::string* name) {
	_name = name;
}

const std::string* contest_info::get_name() const {
	return _name;
}

void contest_info::set_surname(const std::string* surname) {
	_surname = surname;
}

const std::string* contest_info::get_surname() const {
	return _surname;
}

void contest_info::set_patronymic(const std::string* patronymic) {
	_patronymic = patronymic;
}

const std::string* contest_info::get_patronymic() const {
	return _patronymic;
}

void contest_info::set_day_of_birthday(const std::string* day_of_birthday) {
	_day_of_birthday = day_of_birthday;
}

const std::string* contest_info::get_day_of_birthday() const {
	return _day_of_birthday;
}

void contest_info::set_resume(const std::string* resume) {
	_resume = resume;
}

const std::string* contest_info::get_resume() const {
	return _resume;
}

void contest_info::set_id_hrmanager(int id_hrmanager) {
	_id_hrmanager = id_hrmanager;
}

int contest_info::get_id_hrmanager() const {
	return _id_hrmanager;
}

void contest_info::set_id_contest(int id_contest) {
	_id_contest = id_contest;
}

int contest_info::get_id_contest() const {
	return _id_contest;
}

void contest_info::set_prog_lang(const std::string* prog_lang) {
	_prog_lang = prog_lang;
}

const std::string* contest_info::get_prog_lang() const {
	return _prog_lang;
}

void contest_info::set_tasks_count(int tasks_count) {
	_tasks_count = tasks_count;
}

int contest_info::get_tasks_count() const {
	return _tasks_count;
}

void contest_info::set_tasks_complete(int tasks_complete) {
	_tasks_complete = tasks_complete;
}

int contest_info::get_tasks_complete() const {
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
	os << "Full name: " << *info._name << " " << *info._surname << " " << *info._patronymic << " " << std::endl;
	os << "Day of Birthday: " << *info._day_of_birthday << std::endl;
	os << "Summary link: " << *info._resume << std::endl;
	os << "ID HR manager: " << info._id_hrmanager << std::endl;
	os << "ID contest: " << info._id_contest << std::endl;
	os << "Programming language: " << *info._prog_lang << std::endl;
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