#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include "readstring.h"
#include "DataBase.h"
#include "commands.cpp"


int main(int argc, char* argv[]) {

	read_string rstr;

	if (argc != 2) {
		std::cout << "Wrong input" << std::endl;
		return -1;
	}

	std::ifstream file(argv[1]);
	if (!file) {
		std::cout << "File is not opened" << std::endl;
		file.close();
		return -1;
	}
	else {
		data_base d_base;
		while (!file.eof()) {
			char input;
			std::string compare;
			rstr.in_str(&compare, &input, file);
			if (compare.compare("create") == 0) {
				compare = "";
				if (rstr.in_str(&compare, &input, file) != 0) {
					std::cout << "Wrong input in file" << std::endl;
					file.close();
					return -1;
				}
				if (compare.compare("dbase") == 0) {
					compare = "";
					if (rstr.in_str(&compare, &input, file) == 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					// create dbase
					//data_base::flag::Btree
					if (compare.compare("B-tree") == 0) {
						d_base = data_base(data_base::flag::Btree, 3);
					}
					else if (compare.compare("AVL") == 0) {

					}
					else if (compare.compare("RB") == 0) {

					}
					else if (compare.compare("B+-tree") == 0) {

					}
					else if (compare.compare("Splay") == 0) {

					}
					else {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					continue;
				}
				else if (compare.compare("pull") == 0) {
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					std::string name_pull = compare;
					compare = "";
					if (rstr.in_str(&compare, &input, file) == 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					// create pull
					if (compare.compare("B-tree") == 0) {
						d_base.create_pull(name_pull, data_base::flag::Btree, 3);
					}
					else if (compare.compare("AVL") == 0) {

					}
					else if (compare.compare("RB") == 0) {

					}
					else if (compare.compare("B+-tree") == 0) {

					}
					else if (compare.compare("Splay") == 0) {

					}
					else {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					continue;
				}
				else if (compare.compare("scheme") == 0) {
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					std::string pull_name = compare;
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					std::string scheme_name = compare;
					compare = "";
					if (rstr.in_str(&compare, &input, file) == 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					// create scheme
					if (compare.compare("B-tree") == 0) {
						d_base.create_scheme(scheme_name, pull_name, data_base::flag::Btree);
					}
					else if (compare.compare("AVL") == 0) {

					}
					else if (compare.compare("RB") == 0) {

					}
					else if (compare.compare("B+-tree") == 0) {

					}
					else if (compare.compare("Splay") == 0) {

					}
					else {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					continue;

				}
				else if (compare.compare("collection") == 0) {
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					std::string pull_name = compare;
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					std::string scheme_name = compare;
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					std::string name_collection = compare;
					compare = "";
					if (rstr.in_str(&compare, &input, file) == 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					if (compare.compare("B-tree") == 0) {
						d_base.create_collection(name_collection, pull_name, scheme_name, data_base::flag::Btree, 3);
					}
					else if (compare.compare("AVL") == 0) {

					}
					else if (compare.compare("RB") == 0) {

					}
					else if (compare.compare("B+-tree") == 0) {

					}
					else if (compare.compare("Splay") == 0) {

					}
					else {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					//create collection
					continue;
				}
				else {
					std::cout << "Wrong input in file" << std::endl;
					file.close();
					return -1;
				}
				continue;
			}
			else if (compare.compare("delete") == 0) {
				compare = "";
				int temp = rstr.in_str(&compare, &input, file);
				if (compare.compare("dbase") == 0) {
					if (temp == 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					d_base.~data_base();
					//delete dbase
				}
				else if (compare.compare("pull") == 0) {
					if (temp != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					compare = "";
					if (rstr.in_str(&compare, &input, file) == 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					// delete pull
					try {
						d_base.delete_pull(compare);
					}
					catch (std::invalid_argument& e) {
						std::cerr << e.what();
					}
					continue;
				}
				else if (compare.compare("scheme") == 0) {
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					std::string pull_name = compare;
					compare = "";
					if (rstr.in_str(&compare, &input, file) == 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					try {
						d_base.delete_scheme(compare, pull_name);
					}
					catch (std::invalid_argument& e) {
						std::cerr << e.what();
					}
					continue;

				}
				else if (compare.compare("collection") == 0) {
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					std::string pull_name = compare;
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					std::string scheme_name = compare;
					compare = "";
					if (rstr.in_str(&compare, &input, file) == 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					//delete collection
					try {
						d_base.delete_collection(compare, pull_name, scheme_name);
					}
					catch (std::invalid_argument& e) {
						std::cerr << e.what();
					}
					continue;
				}
			}
			else if (compare.compare("collection") == 0) {
				compare = "";
				if (rstr.in_str(&compare, &input, file) != 0) {
					std::cout << "Wrong input in file" << std::endl;
					file.close();
					return -1;
				}
				std::string name_pull = compare;
				compare = "";
				if (rstr.in_str(&compare, &input, file) != 0) {
					std::cout << "Wrong input in file" << std::endl;
					return -1;
				}
				std::string name_scheme = compare;
				compare = "";
				if (rstr.in_str(&compare, &input, file) != 0) {
					std::cout << "Wrong input in file" << std::endl;
					return -1;
				}
				std::string name_collection = compare;
				compare = "";
				if (rstr.in_str(&compare, &input, file) != 0) {
					std::cout << "Wrong input in file" << std::endl;
					file.close();
					return -1;
				}
				// doing function
				invoker my_invoker;
				if (compare.compare("add_node_key") == 0) {
					// check key
					//first key
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					int first_key = std::stoi(compare);
					//second key
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					int second_key = std::stoi(compare);
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					unsigned int id_member = std::stoi(compare);
					compare = "";
					if (rstr.in_str_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					std::string name = compare;
					compare = "";
					if (rstr.in_str_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					std::string surname = compare;
					compare = "";
					if (rstr.in_str_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					std::string patronymic = compare;
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					std::string day_of_birthday = compare;
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					std::string resume = compare;
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					unsigned int id_hrmanager = std::stoi(compare);
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					unsigned int id_contest = std::stoi(compare);
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					std::string prog_lang = compare;
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					unsigned int tasks_count = std::stoi(compare);
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					unsigned int tasks_complete = std::stoi(compare);
					compare = "";
					int flag = rstr.in_str_int(&compare, &input, file);
					if (flag == 0 and flag == 3) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					bool cheating = false;
					if (std::stoi(compare) == 1) {
						cheating = true;
					}
					else if (std::stoi(compare) == 0) {}
					else {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					contest_info member(id_member, name, surname, patronymic, day_of_birthday,
						resume, id_hrmanager, id_contest, prog_lang, tasks_count, tasks_complete,
						cheating);
					std::cout << member << std::endl;
					std::pair<int, int> key_node {first_key, second_key};
					command* add_node_key_command = new add_node_key(
						key_node, &member, d_base.go_to_collection(name_pull, name_scheme, name_collection));
					// add
				}
				else if (compare.compare("read_node_key") == 0) {
					//first key
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					int first_key = std::stoi(compare);
					//second key
					compare = "";
					int flag = rstr.in_str_int(&compare, &input, file);
					if (flag == 0 and flag == 3) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					int second_key = std::stoi(compare);
				}
				else if (compare.compare("read_nodes_keys") == 0) {
					//first_first key
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					int first_first_key = std::stoi(compare);
					//first_second key
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					int first_second_key = std::stoi(compare);
					//second_first key
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					int second_first_key = std::stoi(compare);
					//second_second key
					compare = "";
					int flag = rstr.in_str_int(&compare, &input, file);
					if (flag == 0 and flag == 3) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					int second_second_key = std::stoi(compare);
				}
				else if (compare.compare("update_node_key") == 0) {
					//first key
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					int first_key = std::stoi(compare);
					//second key
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					int second_key = std::stoi(compare);
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					unsigned int id_member = std::stoi(compare);
					compare = "";
					if (rstr.in_str_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					std::string name = compare;
					compare = "";
					if (rstr.in_str_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					std::string surname = compare;
					compare = "";
					if (rstr.in_str_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					std::string patronymic = compare;
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					std::string day_of_birthday = compare;
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					std::string resume = compare;
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					unsigned int id_hrmanager = std::stoi(compare);
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					unsigned int id_contest = std::stoi(compare);
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					std::string prog_lang = compare;
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					unsigned int tasks_count = std::stoi(compare);
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					unsigned int tasks_complete = std::stoi(compare);
					compare = "";
					int flag = rstr.in_str_int(&compare, &input, file);
					if (flag == 0 and flag == 3) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					bool cheating = false;
					if (std::stoi(compare) == 1) {
						cheating = true;
					}
					else if (std::stoi(compare) == 0) {}
					else {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					contest_info member(id_member, name, surname, patronymic, day_of_birthday,
						resume, id_hrmanager, id_contest, prog_lang, tasks_count, tasks_complete,
						cheating);

				}
				else if (compare.compare("remove_node_key") == 0) {
					//first key
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					int first_key = std::stoi(compare);
					//second key
					compare = "";
					int flag = rstr.in_str_int(&compare, &input, file);
					if (flag == 0 and flag == 3) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					int second_key = std::stoi(compare);
				}
				else {
					std::cout << "Wrong input in file" << std::endl;
					file.close();
					return -1;
				}
			}
			else {
				std::cout << "Wrong input in file" << std::endl;
				file.close();
				return -1;
			}
		}
	}

	return 0;
}