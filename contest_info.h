#ifndef CONTEST_INFO
#define CONTEST_INFO

#include <iostream>
#include <string>

class contest_info
{
private:

	unsigned int _id_member;
	std::string _name;
	std::string _surname;
	std::string _patronymic;
	std::string _day_of_birthday;
	std::string _resume;
	unsigned int _id_hrmanager;
	unsigned int _id_contest;
	std::string _prog_lang;
	unsigned int _tasks_count;
	unsigned int _tasks_complete;
	bool _cheating = false;

public:

	contest_info(unsigned int id_member, std::string name, std::string surname,
		std::string patronymic, std::string day_of_birthday, std::string resume,
		unsigned int id_hrmanager, unsigned int id_contest, std::string prog_lang,
		unsigned int tasks_count, unsigned int tasks_complete, bool cheating);

	void set_id_member(unsigned int id_member);

	unsigned int get_id_member() const;

	void set_name(std::string const& name);

	std::string get_name() const;

	void set_surname(std::string surname);

	std::string get_surname() const;

	void set_patronymic(std::string patronymic);

	std::string get_patronymic() const;

	void set_day_of_birthday(std::string day_of_birthday);

	std::string get_day_of_birthday() const;

	void set_resume(std::string resume);

	std::string get_resume() const;

	void set_id_hrmanager(unsigned int id_hrmanager);

	unsigned int get_id_hrmanager() const;

	void set_id_contest(unsigned int id_contest);

	unsigned int get_id_contest() const;

	void set_prog_lang(std::string prog_lang);

	std::string get_prog_lang() const;

	void set_tasks_count(unsigned int tasks_count);

	unsigned int get_tasks_count() const;

	void set_tasks_complete(unsigned int tasks_complete);

	unsigned int get_tasks_complete() const;

	void set_cheating(bool cheating);

	bool get_cheating() const;

	friend std::ostream& operator << (std::ostream& os, const contest_info& info);

};

#endif