#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include "readstring.h"
#include "DataBase.h"
#include "commands.h"
#include <chrono>
#include <ctime>
#include <time.h>
#include <Windows.h>


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
				collection* collection;
				try {
					collection = d_base.go_to_collection(name_pull, name_scheme, name_collection);
				}
				catch (std::invalid_argument& e) {
					std::cerr << e.what();
					file.close();
					return -1;
				}
				invoker my_invoker;
				std::time_t command_time;
				if (compare.compare("add_node_key") == 0) {
					command_time = time(0);
					Sleep(1000);
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					int id_member = std::stoi(compare);
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
					int id_hrmanager = std::stoi(compare);
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					int id_contest = std::stoi(compare);
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
					int tasks_count = std::stoi(compare);
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					int tasks_complete = std::stoi(compare);
					compare = "";
					int flag = rstr.in_str_int(&compare, &input, file);
					if (flag == 3 or flag == 0) {
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
					/*char str[26] = {};
					ctime_s(str, 26, &command_time);
					std::cout << str << std::endl;*/
					contest_info* member = new contest_info(id_member, name, surname, patronymic, day_of_birthday,
						resume, id_hrmanager, id_contest, prog_lang, tasks_count, tasks_complete,
						cheating);
					command* add_node_key_command = new add_node_key(member, collection, command_time);
					try {
						member = collection->find(member);
					}
					catch (std::invalid_argument& e) {
						my_invoker.set_command(add_node_key_command);
						my_invoker.invoke();
					}
					my_invoker.add_command(*member, add_node_key_command);
					// add
				}
				else if (compare.compare("read_node_key") == 0) {
					command_time = time(0);
					//first key
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					int first_key = std::stoi(compare);
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					int second_key = std::stoi(compare);
					//second key
					/*compare = "";
					int flag = rstr.in_str_int(&compare, &input, file);
					if (flag != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					flag = rstr.in_data_str(&compare, &input, file);
					if (flag != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					int data = 0;
					try {
						rstr.in_data(compare, &data);
					}
					catch (std::invalid_argument& e) {
						std::cerr << e.what() << std::endl;
						file.close();
						return -1;
					}*/
					int hours, minutes, seconds;
					if (rstr.in_hour_str((&hours), &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					if (rstr.in_minute_str((&minutes), &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					int flag = rstr.in_seconds_str((&seconds), &input, file);
					if (flag == 3 or flag == 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					command_time = command_time + hours + minutes + seconds;
					std::pair<int, int> key_node {first_key, second_key};
					command* read_node_key_command = new read_node_key(key_node, collection, command_time);
					my_invoker.set_command(read_node_key_command);
					try {
						my_invoker.invoke();
					}
					catch (std::invalid_argument& e) {
						std::cerr << e.what() << std::endl;
					}
				}
				else if (compare.compare("read_node_keys") == 0) {
					command_time = time(0);
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
					if (flag != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					int second_second_key = std::stoi(compare);
					int hours, minutes, seconds;
					if (rstr.in_hour_str((&hours), &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					if (rstr.in_minute_str((&minutes), &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					flag = rstr.in_seconds_str((&seconds), &input, file);
					if (flag == 3 or flag == 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					command_time = command_time + hours + minutes + seconds;
					std::pair<int, int> key_node_1 {first_first_key, first_second_key};
					std::pair<int, int> key_node_2 {second_first_key, second_second_key};
					command* read_node_key_command = new read_node_keys(key_node_1, key_node_2, collection, command_time);
					my_invoker.set_command(read_node_key_command);
					my_invoker.invoke();
				}
				else if (compare.compare("update_node_key") == 0) {
					command_time = time(0);
					Sleep(1000);
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
					std::pair<int, int> key_node {first_key, second_key};
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					std::string flag = compare;
					compare = "";
					command* update_node_key_command;
					if (flag == "id_member") {
						int flag_value = rstr.in_str_int(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						int value = std::stoi(compare);
						update_node_key_command = new update_node_key_id_member(value, command_time);
					}
					else if (flag == "name") {
						int flag_value = rstr.in_str(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						std::string value = compare;
						update_node_key_command = new update_node_key_name(value, command_time);
					}
					else if (flag == "surname") {
						int flag_value = rstr.in_str(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						std::string value = compare;
						update_node_key_command = new update_node_key_surname(value, command_time);
					}
					else if (flag == "patronymic") {
						int flag_value = rstr.in_str(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						std::string value = compare;
						update_node_key_command = new update_node_key_patronymic(value, command_time);
					}
					else if (flag == "day_of_birthday") {
						int flag_value = rstr.in_str(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						std::string value = compare;
						update_node_key_command = new update_node_key_day_of_birthday(value, command_time);
					}
					else if (flag == "resume") {
						int flag_value = rstr.in_str(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						std::string value = compare;
						update_node_key_command = new update_node_key_resume(value, command_time);
					}
					else if (flag == "id_hrmanager") {
						int flag_value = rstr.in_str_int(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						int value = std::stoi(compare);
						update_node_key_command = new update_node_key_id_hrmanager(value, command_time);
					}
					else if (flag == "id_contest") {
						int flag_value = rstr.in_str_int(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						int value = std::stoi(compare);
						update_node_key_command = new update_node_key_id_contest(value, command_time);
					}
					else if (flag == "prog_lang") {
						int flag_value = rstr.in_str(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						std::string value = compare;
						update_node_key_command = new update_node_key_prog_lang(value, command_time);
					}
					else if (flag == "tasks_count") {
						int flag_value = rstr.in_str_int(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						int value = std::stoi(compare);
						update_node_key_command = new update_node_key_tasks_count(value, command_time);
					}
					else if (flag == "tasks_complete") {
						int flag_value = rstr.in_str_int(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						int value = std::stoi(compare);
						update_node_key_command = new update_node_key_tasks_complete(value, command_time);
					}
					else if (flag == "cheating") {
						int flag_cheat = rstr.in_str_int(&compare, &input, file);
						if (flag_cheat == 0 or flag_cheat == 3) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						bool value = false;
						if (std::stoi(compare) == 1) {
							value = true;
						}
						else if (std::stoi(compare) == 0) {}
						else {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						/*int flag_data = rstr.in_data_str(&compare, &input, file);
						if (flag_data == 3 or flag_data == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						int data = 0;
						try {
							rstr.in_data(compare, &data);
						}
						catch (std::invalid_argument& e) {
							std::cerr << e.what() << std::endl;
							file.close();
							return -1;
						}*/
						update_node_key_command = new update_node_key_cheating(value, command_time);
					}
					else {
						std::cout << "Wrong Input" << std::endl;
						file.close();
						return -1;
					}
					
					contest_info* right_member;
					try {
						right_member = d_base.go_to_contest_info(collection, key_node);
					}
					catch (std::invalid_argument& e) {
						std::cerr << e.what() << std::endl;
						file.close();
						return -1;
					}
					try {
						my_invoker.add_command(*right_member, update_node_key_command);
					}
					catch (std::invalid_argument& e) {
						std::cerr << e.what() << std::endl;
					}
				}
				else if (compare.compare("remove_node_key") == 0) {
					command_time = time(0);
					Sleep(1000);
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
					if (flag == 0 or flag == 3) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					int second_key = std::stoi(compare);
					std::pair<int, int> key_node {first_key, second_key};
					command* remove_node_key_command = new remove_node_key(key_node, collection, command_time);
					// get contest_info from collection
					contest_info* member;
					try {
						member = d_base.go_to_contest_info(collection, key_node);
					}
					catch (std::invalid_argument& e) {
						std::cerr << e.what();
						file.close();
						return -1;
					}
					try {
						my_invoker.add_command(*member, remove_node_key_command);
					}
					catch (std::invalid_argument& e) {
						std::cerr << e.what() << std::endl;
					}
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
	file.close();
	return 0;
}