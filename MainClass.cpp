#define _CRT_SECURE_NO_WARNINGS

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
#include <regex>
#include "stringpool.h"
#include "Dialogue_with_user.h"
#include "DataBaseSave.h"


int main(int argc, char* argv[]) {

	//dialogue dl;

	//dl.dialogue_user(argc, argv);

	read_string rstr;
	string_pool* str_p = string_pool::Instance();

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
					const std::string* name_pull = str_p->get_str(compare);
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
					const std::string* pull_name = str_p->get_str(compare);
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					const std::string* scheme_name = str_p->get_str(compare);
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
					const std::string* pull_name = str_p->get_str(compare);
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					const std::string* scheme_name = str_p->get_str(compare);
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					const std::string* name_collection = str_p->get_str(compare);
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
					int flag_name = rstr.in_str(&compare, &input, file);
					if (flag_name == 0 or flag_name == 3) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					const std::string* pull_name = str_p->get_str(compare);
					// delete pull
					try {
						d_base.delete_pull(pull_name);
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
					const std::string* pull_name = str_p->get_str(compare);
					compare = "";
					int flag_name = rstr.in_str(&compare, &input, file);
					if (flag_name == 0 or flag_name == 3) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					const std::string* scheme_name = str_p->get_str(compare);
					try {
						d_base.delete_scheme(scheme_name, pull_name);
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
					const std::string* pull_name = str_p->get_str(compare);
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					const std::string* scheme_name = str_p->get_str(compare);
					compare = "";
					int flag_name = rstr.in_str(&compare, &input, file);
					if (flag_name == 0 or flag_name == 3) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					const std::string* collection_name = str_p->get_str(compare);
					//delete collection
					try {
						d_base.delete_collection(collection_name, pull_name, scheme_name);
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
				const std::string* name_pull = str_p->get_str(compare);
				compare = "";
				if (rstr.in_str(&compare, &input, file) != 0) {
					std::cout << "Wrong input in file" << std::endl;
					return -1;
				}
				const std::string* name_scheme = str_p->get_str(compare);
				compare = "";
				if (rstr.in_str(&compare, &input, file) != 0) {
					std::cout << "Wrong input in file" << std::endl;
					return -1;
				}
				const std::string* name_collection = str_p->get_str(compare);
				compare = "";
				if (rstr.in_str(&compare, &input, file) != 0) {
					std::cout << "Wrong input in file" << std::endl;
					file.close();
					return -1;
				}
				int flag_tree = 0;
				if (compare == "default") {
					flag_tree = 0;
				}
				else if (compare == "resume") {
					flag_tree = 1;
				}
				// doing function
				compare = "";
				if (rstr.in_str(&compare, &input, file) != 0) {
					std::cout << "Wrong input in file" << std::endl;
					file.close();
					return -1;
				}
				std::vector<collection*> vec_coll;
				collection* collection;
				try {
					vec_coll = d_base.go_to_collection(name_pull, name_scheme, name_collection);
				}
				catch (std::invalid_argument& e) {
					std::cerr << e.what();
					file.close();
					return -1;
				}
				if (flag_tree == 0) {
					collection = vec_coll[0];
				}
				else if (flag_tree == 1) {
					collection = vec_coll[1];
				}
				else {
					std::cout << "Wrong Input" << std::endl;
					file.close();
					return -1;
				}
				invoker my_invoker;
				std::time_t command_time;
				time_t input_time;
				static std::regex rgx(R"(((([01][0-9])|(2[0-3]))[:]([0-5][0-9])[:]([0-5][0-9]))[-](0[1-9]|[12][0-9]|3[01])\.(0[1-9]|1[012])\.((19|20)\d\d))");
				static std::regex rgx_data(R"((0[1-9]|[12][0-9]|3[01])\.(0[1-9]|1[012])\.((19|20)\d\d))");
				int year, month, day, hour, minute, seconds;
				std::smatch res;
				struct tm tmp = {0};
				if (compare.compare("add_node_key") == 0) {
					command_time = time(0) - (3*3600);
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
					const std::string* name = str_p->get_str(compare);
					compare = "";
					if (rstr.in_str_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					const std::string* surname = str_p->get_str(compare);
					compare = "";
					if (rstr.in_str_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					const std::string* patronymic = str_p->get_str(compare);
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					if (std::regex_match(compare, res, rgx_data)) {
						day = std::stoi(res[2].str());
						month = (std::stoi(res[3].str()) - 1);
						year = (std::stoi(res[4].str()) - 1900);
						if (month == 1 and day > 29) {
							std::cout << "Wrong day" << std::endl;
							file.close();
							return -1;
						}
						if (month % 2 == 0 and month != 1 and month != 6 and day == 31) {
							std::cout << "Wrong day" << std::endl;
							file.close();
							return -1;
						}
					}
					else {
						std::cout << "Wrong input" << std::endl;
						file.close();
						return -1;
					}
					const std::string* day_of_birthday = str_p->get_str(compare);
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					const std::string* resume = str_p->get_str(compare);
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
					const std::string* prog_lang = str_p->get_str(compare);
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
					//command* add_node_key_command = new add_node_key(member, collection, command_time);
					command* add_node_key_command;
					add_node_key_command = new add_node_key(member, vec_coll[0], command_time);
					try {
						member = vec_coll[0]->find(member);
					}
					catch (std::invalid_argument& e) {
						my_invoker.set_command(add_node_key_command);
						my_invoker.invoke();
					}
					for (int i = 1; i < vec_coll.size(); i++) {
						add_node_key_command = new add_node_key(member, vec_coll[i], command_time);
						try {
							member = vec_coll[i]->find(member);
						}
						catch (std::invalid_argument& e) {
							my_invoker.set_command(add_node_key_command);
							my_invoker.invoke();
						}
					}
					try {
						my_invoker.add_command(*member, add_node_key_command);
					}
					catch (std::invalid_argument& e) {
						std::cerr << e.what() << std::endl;
					}
					// add
				}
				else if (compare.compare("read_node_key") == 0) {
					command_time = time(0);
					//first key
					contest_info key;
					if (flag_tree == 0) {
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
						key.set_id_member(first_key);
						key.set_id_contest(second_key);
					}
					else if (flag_tree == 1) {
						compare = "";
						if (rstr.in_str(&compare, &input, file) != 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						const std::string* key_resume = str_p->get_str(compare);
						key.set_resume(key_resume);
					}
					else {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					compare = "";
					if (rstr.read_data(&compare, &input, file) == 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					if (std::regex_match(compare, res, rgx)) {
						/*char str[26] = {};
						ctime_s(str, 26, &command_time);
						std::cout << str;*/
						tmp = *localtime(&command_time);
						tmp.tm_hour = hour = (std::stoi(res[2].str()) - 3);
						tmp.tm_min = minute = std::stoi(res[5].str());
						tmp.tm_sec = seconds = std::stoi(res[6].str());
						day = std::stoi(res[7].str());
						month = (std::stoi(res[8].str()) - 1);
						year = (std::stoi(res[9].str()) - 1900);
						if (year != (2023 - 1900)) {
							std::cout << "Wrong year" << std::endl;
							file.close();
							return -1;
						}
						if (month == 1 and day > 28) {
							std::cout << "Wrong day" << std::endl;
							file.close();
							return -1;
						}
						if (month % 2 == 0 and month != 1 and month != 6 and day == 31) {
							std::cout << "Wrong day" << std::endl;
							file.close();
							return -1;
						}
						tmp.tm_mday = day;
						tmp.tm_mon = month;
						tmp.tm_year = year;
						input_time = mktime(&tmp);
					}
					else {
						std::cout << "Wrong input" << std::endl;
						file.close();
						return -1;
					}
					command* read_node_key_command = new read_node_key(&key, collection, input_time);
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
					contest_info key1;
					contest_info key2;
					if (flag_tree == 0) {
						compare = "";
						if (rstr.in_str_int(&compare, &input, file) != 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						int first_first_key = std::stoi(compare);
						compare = "";
						if (rstr.in_str_int(&compare, &input, file) != 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						int first_second_key = std::stoi(compare);
						compare = "";
						if (rstr.in_str_int(&compare, &input, file) != 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						int second_first_key = std::stoi(compare);
						compare = "";
						if (rstr.in_str_int(&compare, &input, file) != 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						int second_second_key = std::stoi(compare);
						key1.set_id_member(first_first_key);
						key1.set_id_contest(first_second_key);
						key2.set_id_member(second_first_key);
						key2.set_id_contest(second_second_key);
					}
					else if (flag_tree == 1) {
						compare = "";
						if (rstr.in_str(&compare, &input, file) != 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						const std::string* key1_resume = str_p->get_str(compare);
						compare = "";
						if (rstr.in_str(&compare, &input, file) != 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						const std::string* key2_resume = str_p->get_str(compare);
						key1.set_resume(key1_resume);
						key2.set_resume(key2_resume);
					}
					else {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					compare = "";
					if (rstr.read_data(&compare, &input, file) == 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					if (std::regex_match(compare, res, rgx)) {
						/*char str[26] = {};
						ctime_s(str, 26, &command_time);
						std::cout << str;*/
						tmp = *localtime(&command_time);
						tmp.tm_hour = hour = (std::stoi(res[2].str()) - 3);
						tmp.tm_min = minute = std::stoi(res[5].str());
						tmp.tm_sec = seconds = std::stoi(res[6].str());
						day = std::stoi(res[7].str());
						month = (std::stoi(res[8].str()) - 1);
						year = (std::stoi(res[9].str()) - 1900);
						if (year != (2023 - 1900)) {
							std::cout << "Wrong year" << std::endl;
							file.close();
							return -1;
						}
						if (month == 1 and day > 28) {
							std::cout << "Wrong day" << std::endl;
							file.close();
							return -1;
						}
						if (month % 2 == 0 and month != 1 and month != 6 and day == 31) {
							std::cout << "Wrong day" << std::endl;
							file.close();
							return -1;
						}
						tmp.tm_mday = day;
						tmp.tm_mon = month;
						tmp.tm_year = year;
						input_time = mktime(&tmp);
					}
					else {
						std::cout << "Wrong input" << std::endl;
						file.close();
						return -1;
					}
					command* read_node_keys_command = new read_node_keys(&key1, &key2, collection, input_time, flag_tree);
					my_invoker.set_command(read_node_keys_command);
					try {
						my_invoker.invoke();
					}
					catch (std::invalid_argument& e) {
						std::cerr << e.what() << std::endl;
					}
				}
				else if (compare.compare("update_node_key") == 0) {
					command_time = time(0) - (3 * 3600);
					//first key
					contest_info key;
					if (flag_tree == 0) {
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
						key.set_id_member(first_key);
						key.set_id_contest(second_key);
					}
					else if (flag_tree == 1) {
						compare = "";
						if (rstr.in_str(&compare, &input, file) != 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						const std::string* key_resume = str_p->get_str(compare);
						key.set_resume(key_resume);
					}
					else {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					const std::string* flag = str_p->get_str(compare);
					compare = "";
					command* update_node_key_command;
					if (*flag == "id_member") {
						int flag_value = rstr.in_str_int(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						int value = std::stoi(compare);
						update_node_key_command = new update_node_key_id_member(value, command_time);
					}
					else if (*flag == "name") {
						int flag_value = rstr.in_str(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						const std::string* value = str_p->get_str(compare);
						update_node_key_command = new update_node_key_name(value, command_time);
					}
					else if (*flag == "surname") {
						int flag_value = rstr.in_str(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						const std::string * value = str_p->get_str(compare);
						update_node_key_command = new update_node_key_surname(value, command_time);
					}
					else if (*flag == "patronymic") {
						int flag_value = rstr.in_str(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						const std::string* value = str_p->get_str(compare);
						update_node_key_command = new update_node_key_patronymic(value, command_time);
					}
					else if (*flag == "day_of_birthday") {
						int flag_value = rstr.in_str(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						if (std::regex_match(compare, res, rgx_data)) {
							day = std::stoi(res[2].str());
							month = (std::stoi(res[3].str()) - 1);
							year = (std::stoi(res[4].str()) - 1900);
							if (month == 1 and day > 29) {
								std::cout << "Wrong day" << std::endl;
								file.close();
								return -1;
							}
							if (month % 2 == 0 and month != 1 and month != 6 and day == 31) {
								std::cout << "Wrong day" << std::endl;
								file.close();
								return -1;
							}
						}
						else {
							std::cout << "Wrong input" << std::endl;
							file.close();
							return -1;
						}
						const std::string* value = str_p->get_str(compare);
						update_node_key_command = new update_node_key_day_of_birthday(value, command_time);
					}
					else if (*flag == "resume") {
						int flag_value = rstr.in_str(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						const std::string* value = str_p->get_str(compare);
						update_node_key_command = new update_node_key_resume(value, command_time);
					}
					else if (*flag == "id_hrmanager") {
						int flag_value = rstr.in_str_int(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						int value = std::stoi(compare);
						update_node_key_command = new update_node_key_id_hrmanager(value, command_time);
					}
					else if (*flag == "id_contest") {
						int flag_value = rstr.in_str_int(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						int value = std::stoi(compare);
						update_node_key_command = new update_node_key_id_contest(value, command_time);
					}
					else if (*flag == "prog_lang") {
						int flag_value = rstr.in_str(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						const std::string* value = str_p->get_str(compare);
						update_node_key_command = new update_node_key_prog_lang(value, command_time);
					}
					else if (*flag == "tasks_count") {
						int flag_value = rstr.in_str_int(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						int value = std::stoi(compare);
						update_node_key_command = new update_node_key_tasks_count(value, command_time);
					}
					else if (*flag == "tasks_complete") {
						int flag_value = rstr.in_str_int(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						int value = std::stoi(compare);
						update_node_key_command = new update_node_key_tasks_complete(value, command_time);
					}
					else if (*flag == "cheating") {
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
						right_member = d_base.go_to_contest_info(collection, &key);
					}
					catch (std::invalid_argument& e) {
						std::cerr << e.what() << std::endl;
						file.close();
						return -1;
					}
					if (flag_tree == 0) {
						comparer_id_member_id_contest _comp;
						if (dynamic_cast<Btree<contest_info*, contest_info*, comparer_id_member_id_contest>*>((collection_default*)vec_coll[flag_tree])) {
							Btree<contest_info*, contest_info*, comparer_id_member_id_contest>* _btree =
								dynamic_cast<Btree<contest_info*, contest_info*, comparer_id_member_id_contest>*>((collection_default*)vec_coll[flag_tree]);
							command* temp;
							contest_info copy_value;
							auto it = _btree->infix_iterator_begin();
							for (it; it != _btree->infix_iterator_end(); ++it) {
								if (_comp.comparate(std::get<0>(*it), &key) == 0) {
									my_invoker.add_command(*std::get<1>(*it), update_node_key_command);
									break;
								}
							}
						}
					}
					else if (flag_tree == 1) {
						comparer_resume _comp_resume;
						if (dynamic_cast<Btree<contest_info*, contest_info*, comparer_resume>*>((collection_resume*)vec_coll[flag_tree])) {
							Btree<contest_info*, contest_info*, comparer_resume>* _btree =
								dynamic_cast<Btree<contest_info*, contest_info*, comparer_resume>*>((collection_default*)vec_coll[flag_tree]);
							command* temp;
							contest_info copy_value;
							auto it = _btree->infix_iterator_begin();
							for (it; it != _btree->infix_iterator_end(); ++it) {
								if (_comp_resume.comparate(std::get<0>(*it), &key) == 0) {
									try {
										my_invoker.add_command(*std::get<1>(*it), update_node_key_command);
									}
									catch (std::invalid_argument& e) {
										std::cerr << e.what() << std::endl;
									}
									break;
								}
							}
						}
					}
					else {
						std::cout << "Wrong tree" << std::endl;
						file.close();
						return -1;
					}
				}
				else if (compare.compare("remove_node_key") == 0) {
					command_time = time(0) - (3 * 3600);
					//first key
					contest_info key;
					if (flag_tree == 0) {
						compare = "";
						if (rstr.in_str_int(&compare, &input, file) != 0) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						int first_key = std::stoi(compare);
						compare = "";
						int flag_remove = rstr.in_str_int(&compare, &input, file);
						if (flag_remove == 0 or flag_remove == 3) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						int second_key = std::stoi(compare);
						key.set_id_member(first_key);
						key.set_id_contest(second_key);
					}
					else if (flag_tree == 1) {
						compare = "";
						int flag_remove = rstr.in_str(&compare, &input, file);

						if (flag_remove == 0 or flag_remove == 3) {
							std::cout << "Wrong input in file" << std::endl;
							file.close();
							return -1;
						}
						const std::string* key_resume = str_p->get_str(compare);
						key.set_resume(key_resume);
					}
					else {
						std::cout << "Wrong input in file" << std::endl;
						file.close();
						return -1;
					}
					// get contest_info from collection
					contest_info* member;
					
					command* remove_node_key_command = new remove_node_key(&key, vec_coll[flag_tree], command_time);
					try {
						member = d_base.go_to_contest_info(vec_coll[flag_tree], &key);
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
					try {
						member = d_base.go_to_contest_info(collection, &key);
					}
					catch (std::invalid_argument& e) {
						std::cerr << e.what();
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
			else if (compare == "save") {
				compare = "";
				int flag_save = rstr.in_str(&compare, &input, file);
				if (flag_save == 0 or flag_save == 3) {
					std::cout << "Wrong input in file" << std::endl;
					file.close();
					return -1;
				}
				dbase_safe saver(compare, &d_base, data_base::flag::Btree);
				saver.save();
			}
			else if (compare == "upload") {
				compare = "";
				int flag_save = rstr.in_str(&compare, &input, file);
				if (flag_save == 0 or flag_save == 3) {
					std::cout << "Wrong input in file" << std::endl;
					file.close();
					return -1;
				}
				data_base d_base = data_base(data_base::flag::Btree, 3);
				dbase_safe saver(compare, &d_base, data_base::flag::Btree);
				saver.restore();
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