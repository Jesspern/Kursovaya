#include "commands.h"

void add_node_key::execute()
{
	// check key
	_tree->insert(_key, _value);
}

void read_node_key::execute()
{
	contest_info* value;
	try {
		value = _tree->find(_key);
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("ID is not correct");
	}
	// check what value
	std::cout << value << std::endl;
}

void update_node_key::execute()
{
	contest_info* value;
	try {
		if (dynamic_cast<Btree<std::pair<int, int>, contest_info*, comparer>*>(_tree)) {
			Btree<std::pair<int, int>, contest_info*, comparer>* _btree =
				dynamic_cast<Btree<std::pair<int, int>, contest_info*, comparer>*>(_tree);
			value = _btree->swap_value(_key, _value);
		}
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("ID is not correct");
	}
	// check what value
	std::cout << value << std::endl;
}

void remove_node_key::execute()
{
	contest_info* value;
	try {
		value = _tree->remove(_key);
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("ID is not correct");
	}
	// check what value
	std::cout << value << std::endl;
}

void read_node_keys::execute()
{
	contest_info* value;
	try {
		value = _tree->find(_key1);
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("ID is not correct");
	}
	if (dynamic_cast<Btree<std::pair<int, int>, contest_info*, comparer>*>(_tree)) {
		Btree<std::pair<int, int>, contest_info*, comparer>* _btree = dynamic_cast<Btree<std::pair<int, int>, contest_info*, comparer>*>(_tree);
		for (auto it = _btree->infix_iterator_begin(); it != _btree->infix_iterator_end(); it++) {
			if (std::get<0>(*it) > _key2) {
				break;
			}
			if (std::get<0>(*it) >= _key1) {
				std::cout << (std::get<1>(*it))->get_name() << std::endl;
			}
		}
	}
	else {

	}
}

void invoker::set_command(command* cmd) {
	_cmd = cmd;
}

void invoker::invoke() {
	_cmd->execute();
}