#ifndef COMMANDS
#define COMMANDS

#include <iostream>
#include "command.h"
#include "contest_info.h"
#include "DataBase.h"

class add_node_key final : public command {

private:

	contest_info* _value;
	collection* _tree;

public:

	add_node_key(contest_info* value, collection* tree, long long data) :
		_value(value), _tree(tree) {
		_time = data;
	}
	void execute() override;

	void execute(contest_info& clone) override;

	contest_info get_value();

	~add_node_key() override = default;

};

class read_node_key final : public command {

private:

	contest_info* _key;
	collection* _tree;

public:

	read_node_key(contest_info* key, collection* tree, long long data) : _key(key), _tree(tree) {
		_time = data;
	}

	void execute() override;

	void execute(contest_info& clone) override {}

	~read_node_key() override = default;

};

class update_node_key_id_member final : public command {

private:

	int _value;


public:

	update_node_key_id_member(int value, int data) : _value(value) {
		_time = data;
	}

	void execute() override {}

	void execute(contest_info& clone);

	~update_node_key_id_member() override = default;
};

class update_node_key_name final : public command {

private:

	const std::string* _value;


public:

	update_node_key_name(const std::string* value, long long data) : _value(value) {
		_time = data;
	};

	void execute() override {}

	void execute(contest_info& clone) override;

	std::string get_value();

	~update_node_key_name() override = default;
};

class update_node_key_surname final : public command {
private:

	const std::string* _value;


public:

	update_node_key_surname(const std::string* value, long long data) : _value(value) {
		_time = data;
	};

	void execute() override {}

	void execute(contest_info& clone) override;

	std::string get_value();

	~update_node_key_surname() override = default;
};

class update_node_key_patronymic final : public command {
private:

	const std::string* _value;


public:

	update_node_key_patronymic(const std::string* value, long long data) : _value(value) {
		_time = data;
	};

	void execute() override {}

	void execute(contest_info& clone) override;

	std::string get_value();

	~update_node_key_patronymic() override = default;
};

class update_node_key_day_of_birthday final : public command {
private:

	const std::string* _value;


public:

	update_node_key_day_of_birthday(const std::string* value, long long data) : _value(value) {
		_time = data;
	};

	void execute() override {}

	void execute(contest_info& clone) override;

	std::string get_value();

	~update_node_key_day_of_birthday() override = default;
};

class update_node_key_resume final : public command {
private:

	const std::string* _value;


public:

	update_node_key_resume(const std::string* value, long long data) : _value(value) {
		_time = data;
	};

	void execute() override {}

	void execute(contest_info& clone) override;

	~update_node_key_resume() override = default;
};

class update_node_key_id_hrmanager final : public command {
private:

	int _value;


public:

	update_node_key_id_hrmanager(int value, long long data) : _value(value) {
		_time = data;
	};

	void execute() override {}

	void execute(contest_info& clone) override;

	int get_value();

	~update_node_key_id_hrmanager() override = default;
};

class update_node_key_id_contest final : public command {
private:

	int _value;


public:

	update_node_key_id_contest(int value, long long data) : _value(value) {
		_time = data;
	};

	void execute() override {}

	void execute(contest_info& clone) override;

	~update_node_key_id_contest() override = default;
};

class update_node_key_prog_lang final : public command {
private:

	const std::string* _value;


public:

	update_node_key_prog_lang(const std::string* value, long long data) : _value(value) {
		_time = data;
	};

	void execute() override {}

	void execute(contest_info& clone) override;

	std::string get_value();

	~update_node_key_prog_lang() override = default;
};

class update_node_key_tasks_count final : public command {
private:

	int _value;


public:

	update_node_key_tasks_count(int value, long long data) : _value(value) {
		_time = data;
	};

	void execute() override {}

	void execute(contest_info& clone) override;

	int get_value();

	~update_node_key_tasks_count() override = default;
};

class update_node_key_tasks_complete final : public command {
private:

	int _value;


public:

	update_node_key_tasks_complete(int value, long long data) : _value(value) {
		_time = data;
	};

	void execute() override {}

	void execute(contest_info& clone) override;

	int get_value();

	~update_node_key_tasks_complete() override = default;
};

class update_node_key_cheating final : public command {
private:

	bool _value;


public:

	update_node_key_cheating(bool value, long long data) : _value(value) {
		_time = data;
	};

	void execute() override {}

	void execute(contest_info& clone) override;

	bool get_value();

	~update_node_key_cheating() override = default;
};


class remove_node_key final : public command {

private:

	contest_info* _key;
	collection* _tree;

public:

	remove_node_key(contest_info* key, collection* tree, long long data) : _key(key), _tree(tree) {
		_time = data;
	}

	void execute() override;

	void execute(contest_info& clone) override {}

	contest_info get_value();

	~remove_node_key() override = default;

};

class read_node_keys final : public command {

private:

	contest_info* _key1;
	contest_info* _key2;
	collection* _tree;
	int _flag;

public:

	read_node_keys(contest_info* key1, contest_info* key2, collection* tree, long long data, int flag) :
		_key1(key1), _key2(key2), _tree(tree), _flag(flag) {
		_time = data;
	}

	void execute() override;

	void execute(contest_info& clone) override {}

	~read_node_keys() override = default;

};

class invoker final {

private:

	command* _cmd;

	contest_info* clone;

public:

	//invoker& operator->();

	void add_command(contest_info& info, command* cmd);

	void set_command(command* cmd);

	void invoke();

	~invoker() = default;
};
#endif