#include "commands.h"

void add_node_key::execute()
{
	// check key
	int checker = 0;
	try {
		_tree->find(_value);
	}
	catch (std::invalid_argument&) {
		checker = 1;
	}
	if (checker) {
		_tree->insert(_value, _value);
	}
	else {
		throw std::invalid_argument("Key is already added");
	}
}

void add_node_key::execute(contest_info& clone)
{
	clone = *_value;
}

contest_info add_node_key::get_value() {
	return *_value;
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
	command* temp = value->first_command;
	contest_info copy_value = *value;
	if (temp == nullptr or temp->_time > _time) {
		throw std::invalid_argument("Element dont exist");
	}
	else {
		temp = temp->next_command;
	}
	while (temp != nullptr and temp->_time < _time) {
		if (dynamic_cast<remove_node_key*>(temp)) {
			if (temp->next_command == nullptr) {
				throw std::invalid_argument("Element has been deleted");
			}
		}
		else if (dynamic_cast<add_node_key*>(temp)) {
			temp->execute(copy_value);
		}
		else {
			temp->execute(copy_value);
		}
		temp = temp->next_command;
	}
	std::cout << copy_value << std::endl;
}

void update_node_key_id_member::execute(contest_info& clone) {
	clone.set_id_member(_value);
}

std::string update_node_key_name::get_value() {
	return *_value;
}

void update_node_key_name::execute(contest_info& clone) {
	clone.set_name(_value);
}

std::string update_node_key_surname::get_value() {
	return *_value;
}

void update_node_key_surname::execute(contest_info& clone) {
	clone.set_surname(_value);
}

std::string update_node_key_patronymic::get_value() {
	return *_value;
}

void update_node_key_patronymic::execute(contest_info& clone) {
	clone.set_patronymic(_value);
}

std::string update_node_key_day_of_birthday::get_value() {
	return *_value;
}

void update_node_key_day_of_birthday::execute(contest_info& clone) {
	clone.set_day_of_birthday(_value);
}

void update_node_key_resume::execute(contest_info& clone) {
	clone.set_resume(_value);
}

int update_node_key_id_hrmanager::get_value() {
	return _value;
}

void update_node_key_id_hrmanager::execute(contest_info& clone) {
	clone.set_id_hrmanager(_value);
}

void update_node_key_id_contest::execute(contest_info& clone) {
	clone.set_id_contest(_value);
}

std::string update_node_key_prog_lang::get_value() {
	return *_value;
}

void update_node_key_prog_lang::execute(contest_info& clone) {
	clone.set_prog_lang(_value);
}

int update_node_key_tasks_count::get_value() {
	return _value;
}

void update_node_key_tasks_count::execute(contest_info& clone) {
	clone.set_tasks_count(_value);
}

int update_node_key_tasks_complete::get_value() {
	return _value;
}

void update_node_key_tasks_complete::execute(contest_info& clone) {
	clone.set_tasks_complete(_value);
}

bool update_node_key_cheating::get_value() {
	return _value;
}

void update_node_key_cheating::execute(contest_info& clone) {
	clone.set_cheating(_value);
}

contest_info remove_node_key::get_value() {
	return *_key;
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
	std::cout << *value << std::endl;
}

void read_node_keys::execute()
{
	comparer_id_member_id_contest _comp;
	contest_info* value;
	try {
		value = _tree->find(_key1);
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("ID is not correct");
	}
	if (_flag == 0) {
		if (dynamic_cast<Btree<contest_info*, contest_info*, comparer_id_member_id_contest>*>((collection_default*)_tree)) {
			Btree<contest_info*, contest_info*, comparer_id_member_id_contest>* _btree = dynamic_cast<Btree<contest_info*, contest_info*, comparer_id_member_id_contest>*>((collection_default*)_tree);
			command* temp;
			contest_info copy_value;
			auto it = _btree->infix_iterator_begin();
			for (it; it != _btree->infix_iterator_end(); ++it) {
				if (_comp.comparate(std::get<0>(*it), _key2) == 1) {
					break;
				}
				if (_comp.comparate(std::get<0>(*it), _key2) == 2 or _comp.comparate(std::get<0>(*it), _key2) == 0) {
					//std::cout << (std::get<1>(*it)) << std::endl;
					temp = (std::get<1>(*it))->first_command;
					copy_value = *(std::get<1>(*it));
					if (temp == nullptr or temp->_time > _time) {
						throw std::invalid_argument("Element dont exist");
					}
					else {
						temp = temp->next_command;
					}
					while (temp != nullptr and temp->_time < _time) {
						if (dynamic_cast<remove_node_key*>(temp)) {
							if (temp->next_command == nullptr) {
								throw std::invalid_argument("Element has been deleted");
							}
						}
						else if (dynamic_cast<add_node_key*>(temp)) {
							temp->execute(copy_value);
						}
						else {
							temp->execute(copy_value);
						}
						temp = temp->next_command;
					}
					std::cout << copy_value << std::endl;
				}
			}
		}

	}
	else if (_flag == 1) {
		if (dynamic_cast<Btree<contest_info*, contest_info*, comparer_resume>*>((collection_resume*)_tree)) {
			Btree<contest_info*, contest_info*, comparer_resume>* _btree = dynamic_cast<Btree<contest_info*, contest_info*, comparer_resume>*>((collection_default*)_tree);
			command* temp;
			contest_info copy_value;
			auto it = _btree->infix_iterator_begin();
			for (it; it != _btree->infix_iterator_end(); ++it) {
				if (_comp.comparate(std::get<0>(*it), _key2) == 1) {
					break;
				}
				if (_comp.comparate(std::get<0>(*it), _key2) == 2 or _comp.comparate(std::get<0>(*it), _key2) == 0) {
					//std::cout << (std::get<1>(*it)) << std::endl;
					temp = (std::get<1>(*it))->first_command;
					copy_value = *(std::get<1>(*it));
					if (temp == nullptr or temp->_time > _time) {
						throw std::invalid_argument("Element dont exist");
					}
					else {
						temp = temp->next_command;
					}
					while (temp != nullptr and temp->_time < _time) {
						if (dynamic_cast<remove_node_key*>(temp)) {
							if (temp->next_command == nullptr) {
								throw std::invalid_argument("Element has been deleted");
							}
						}
						else if (dynamic_cast<add_node_key*>(temp)) {
							temp->execute(copy_value);
						}
						else {
							temp->execute(copy_value);
						}
						temp = temp->next_command;
					}
					std::cout << copy_value << std::endl;
				}
			}
		}

	}

}

//invoker& invoker::operator->() {
//	return *this;
//}
//
void invoker::add_command(contest_info& info, command* cmd) {
 	command* temp = info.first_command;
	if (temp == nullptr) {
		if (dynamic_cast<add_node_key*>(cmd)) {
			info.first_command = cmd;
		}
		else {
			throw std::invalid_argument("Problem with commands");
		}
	}
	else {
		while (temp->next_command != nullptr) {
			temp = temp->next_command;
		}
		if (dynamic_cast<remove_node_key*>(temp)) {
			if (dynamic_cast<add_node_key*>(cmd)) {
				temp->next_command = cmd;
			}
			else {
				throw std::invalid_argument("This element has been deleted. It can not be changed");
			}
		}
		else {
			temp->next_command = cmd;
		}
	}
}

void invoker::set_command(command* cmd) {
	_cmd = cmd;
}

void invoker::invoke() {
	_cmd->execute();
}