#ifndef COMMANDS
#define COMMANDS

#include <iostream>
#include "command.cpp"
#include "contest_info.h"
#include "DataBase.h"

class add_node_key final : public command {

private:

	std::pair<int, int> _key;
	contest_info* _value;
	collection* _tree;

public:

	add_node_key(std::pair<int, int> key, contest_info* value, collection* tree) :
		_key(key), _value(value), _tree(tree) {}

	void execute() override;

	~add_node_key() override = default;

};

class read_node_key final : public command {

private:

	std::pair<int, int> _key;
	collection* _tree;

private:

	read_node_key(std::pair<int, int> key, collection* tree) : _key(key), _tree(tree) {}

	void execute() override;

	~read_node_key() override = default;

};

class update_node_key final : public command {

private:

	std::pair<int, int> _key;
	contest_info* _value;
	collection* _tree;

private:

	update_node_key(std::pair<int, int> key, contest_info* value, collection* tree) :
		_key(key), _value(value), _tree(tree) {}

	void execute() override;

	~update_node_key() override = default;

};

class remove_node_key final : public command {

private:

	std::pair<int, int> _key;
	collection* _tree;

private:

	remove_node_key(std::pair<int, int> key, collection* tree) : _key(key), _tree(tree) {}

	void execute() override;

	~remove_node_key() override = default;

};

class read_node_keys final : public command {

private:

	std::pair<int, int> _key1;
	std::pair<int, int> _key2;
	collection* _tree;

private:

	read_node_keys(std::pair<int, int> key1, std::pair<int, int> key2, collection* tree) :
		_key1(key1), _key2(key2), _tree(tree) {}

	void execute() override;

	~read_node_keys() override = default;

};

class invoker final {

private:

	command* _cmd;

public:

	void set_command(command* cmd);

	void invoke();

};
#endif