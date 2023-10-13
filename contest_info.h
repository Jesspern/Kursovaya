#ifndef CONTEST_INFO
#define CONTEST_INFO

#include <iostream>
#include <string>
#include "contest_info.h"
#include "command.h"
#include <list>

class contest_info
{
private:

	int _id_member;
	std::string _name;
	std::string _surname;
	std::string _patronymic;
	std::string _day_of_birthday;
	std::string _resume;
	int _id_hrmanager;
	int _id_contest;
	std::string _prog_lang;
	int _tasks_count;
	int _tasks_complete;
	bool _cheating = false;

public:

	command* first_command;

	contest_info() = default;

	contest_info(int id_member, std::string name, std::string surname,
		std::string patronymic, std::string day_of_birthday, std::string resume,
		int id_hrmanager, int id_contest, std::string prog_lang,
		int tasks_count, int tasks_complete, bool cheating);

	~contest_info() = default;

	contest_info& operator=(const contest_info& other);
	
	void set_id_member(int id_member);

	int get_id_member() const;

	void set_name(std::string const& name);

	std::string get_name() const;

	void set_surname(std::string const& surname);

	std::string get_surname() const;

	void set_patronymic(std::string const& patronymic);

	std::string get_patronymic() const;

	void set_day_of_birthday(std::string const& day_of_birthday);

	std::string get_day_of_birthday() const;

	void set_resume(std::string const& resume);

	std::string get_resume() const;

	void set_id_hrmanager(int id_hrmanager);

	int get_id_hrmanager() const;

	void set_id_contest(int id_contest);

	int get_id_contest() const;

	void set_prog_lang(std::string const& prog_lang);

	std::string get_prog_lang() const;

	void set_tasks_count(int tasks_count);

	int get_tasks_count() const;

	void set_tasks_complete(int tasks_complete);

	int get_tasks_complete() const;

	void set_cheating(bool cheating);

	bool get_cheating() const;

	friend std::ostream& operator << (std::ostream& os, const contest_info& info);

};

#endif