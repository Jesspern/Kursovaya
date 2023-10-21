#include "Dialogue_with_user.h"

void dialogue::dialogue_user(int argc, char* argv[]) {
	int flag;
	bool flag_dbase = false;
	
	string_pool* str_p = string_pool::Instance();

	std::cout << "Do you want upload tree or do new?" << std::endl << "1. Yes" << std::endl << "2. No" << std::endl;

	std::cin >> flag;

	if (flag == 1) {
		// upload
		flag_dbase = true;
	}
	else if (flag == 2) {
		//
	}
	else {
		std::cout << "Wrong input" << std::endl;
		throw std::invalid_argument("Wrong number");
	}

	std::cout << "Choose how you want to input?" << std::endl << "1. With console" << std::endl << "2. With file" << std::endl;

	std::cin >> flag;
	//data_base d_base;
	std::string nameofpull;
	std::string nameofscheme;
	std::string nameofcollection;

	if (flag == 1) {
		
		while (true) {
			std::cout << "Now you can choose what commands you want to do" << std::endl << "1. Create dbase" << std::endl
				<< "2. Create pool" << std::endl << "3. Create scheme" << std::endl << "4. Create collection" << std::endl << "5. Delete dbase" << std::endl
				<< "6. Delete pool" << std::endl << "7. Delete scheme" << std::endl << "8. Delete collection" << std::endl << "9. Commands collection" << std::endl
				<< "10. Save data base" << std::endl << "11. End program" << std::endl;
			std::cin >> flag;
			if (flag == 10) {
				break;
			}
			switch (flag) {
			case 1:
				if (flag_dbase) {
					std::cout << "Data base already exist" << std::endl;
				}
				else {
					// create dbase
					std::cout << "Now we need to create data base. Choose what tree will be data base." << std::endl
						<< "1. B-tree" << std::endl << "2. AVL tree" << std::endl << "3. Splay tree" << std::endl << "4. RB tree" << std::endl;

					std::cin >> flag;
					switch (flag) {
					case 1:
						//d_base = data_base(data_base::flag::Btree, 3);
						//create tree
						break;
					case 2:
						//create tree
						break;
					case 3:
						//create tree
						break;
					case 4:
						//create tree
						break;
					default:
						throw std::invalid_argument("Wrong input tree");

					}

				}
				break;
			case 2:
				std::cout << "Now you are creating pool. Choose what tree will be pool." << std::endl
					<< "1. B-tree" << std::endl << "2. AVL tree" << std::endl << "3. Splay tree" << std::endl << "4. RB tree" << std::endl;

				std::cin >> flag;

				std::cout << "Pls input name of pull" << std::endl;
				
				std::cin >> nameofpull;
				switch (flag) {
				case 1:
					//d_base.create_pull(nameofpull, data_base::flag::Btree, 3);
					//create tree
					break;
				case 2:
					//create tree
					break;
				case 3:
					//create tree
					break;
				case 4:
					//create tree
					break;
				default:
					throw std::invalid_argument("Wrong input tree");

				}
				break;
			case 3:
				std::cout << "Now you are creating scheme. Choose what tree will be scheme." << std::endl
					<< "1. B-tree" << std::endl << "2. AVL tree" << std::endl << "3. Splay tree" << std::endl << "4. RB tree" << std::endl;

				std::cin >> flag;

				std::cout << "Pls input name of pull and name of scheme" << std::endl;

				std::cin >> nameofpull;
				std::cin >> nameofscheme;
				switch (flag) {
				case 1:
					//d_base.create_scheme(nameofscheme, nameofpull, data_base::flag::Btree);;
					//create tree
					break;
				case 2:
					//create tree
					break;
				case 3:
					//create tree
					break;
				case 4:
					//create tree
					break;
				default:
					throw std::invalid_argument("Wrong input tree");

				}
				break;
			case 4:
				std::cout << "Now you are creating collection. Choose what tree will be collection." << std::endl
					<< "1. B-tree" << std::endl << "2. AVL tree" << std::endl << "3. Splay tree" << std::endl << "4. RB tree" << std::endl;

				std::cin >> flag;

				std::cout << "Pls input name of pull, name of scheme and name of collection" << std::endl;

				std::cin >> nameofpull;
				std::cin >> nameofscheme;
				std::cin >> nameofcollection;
				switch (flag) {
				case 1:
					//d_base.create_collection(*nameofcollection, *nameofscheme, *nameofpull, data_base::flag::Btree, 3);
					//create tree
					break;
				case 2:
					//create tree
					break;
				case 3:
					//create tree
					break;
				case 4:
					//create tree
					break;
				default:
					throw std::invalid_argument("Wrong input tree");

				}
				break;
			case 5:
				std::cout << "Now you are deleting dbase." << std::endl;
				// d_base.~data_base();
				break;
			case 6:
				std::cout << "Now you are deleting pool." << std::endl;

				std::cout << "Pls input name of pull" << std::endl;

				std::cin >> nameofpull;
				/*try {
					d_base.delete_pull(compare);
				}
				catch (std::invalid_argument& e) {
					std::cerr << e.what();
				}*/
				break;
			case 7:
				std::cout << "Now you are deleting scheme." << std::endl;

				std::cout << "Pls input name of pull and name of scheme" << std::endl;

				std::cin >> nameofpull;
				std::cin >> nameofscheme;

				/*try {
					d_base.delete_scheme(compare, *pull_name);
				}
				catch (std::invalid_argument& e) {
					std::cerr << e.what();
				}*/
				break;
			case 8:
				std::cout << "Now you are deleting collection." << std::endl;

				std::cout << "Pls input name of pull, name of scheme and name of collection" << std::endl;

				std::cin >> nameofpull >> nameofscheme >> nameofcollection;
				/*try {
					d_base.delete_collection(compare, *pull_name, *scheme_name);
				}
				catch (std::invalid_argument& e) {
					std::cerr << e.what();
				}*/
				break;
			case 9:
				while (true) {
					std::cout << "You need to write 'name of pool' 'name of scheme' 'name of collection'" << std::endl;
					std::string pool, scheme, collection;
					std::cin >> pool >> scheme >> collection;
					int flag_key;

					/*std::vector<collection*> vec_coll;
					collection* collection;
					try {
						vec_coll = d_base.go_to_collection(*name_pull, *name_scheme, *name_collection);
					}
					catch (std::invalid_argument& e) {
						std::cerr << e.what();
						file.close();
						return -1;
					}*/

					std::cout << "Now you can choose key what you want." << std::endl << "1. default key(id_member, id_contest)" << std::endl
						<< "2. resume key" << std::endl;

					std::cin >> flag_key;
					if (flag_key != 1 and flag_key != 2) {
						std::cout << "Wrong choosen key" << std::endl;
					}

					std::time_t command_time;
					time_t input_time;
					// can add cycle for this collection
					
					std::cout << "Choose command." << std::endl << "1. Add contest (add_node_key)" << std::endl << "2. Update contest (update_node_key)"
						<< std::endl << "3. Remove contest (remove_node_key)" << std::endl << "4. Read contest (read_node_key)" << std::endl <<
						"5. Read contests (read_nodes_key)" << std::endl << "6. End input commands" << std::endl;
					std::cin >> flag;

					if (flag == 6) {
						break;
					}
					std::string input;
					int id_member; 
					const std::string* name;
					const std::string* surname;
					const std::string* patronymic;
					const std::string* day_of_birthday;
					const std::string* resume;
					int id_hrmanager;
					int id_contest;
					const std::string* prog_lang;
					int tasks_count;
					int tasks_complete;
					bool cheating = false;
					static std::regex rgx(R"(((([01][0-9])|(2[0-3]))[:]([0-5][0-9])[:]([0-5][0-9]))[-](0[1-9]|[12][0-9]|3[01])\.(0[1-9]|1[012])\.((19|20)\d\d))");
					static std::regex rgx_data(R"((0[1-9]|[12][0-9]|3[01])\.(0[1-9]|1[012])\.((19|20)\d\d))");
					int year, month, day, hour, minute, seconds;
					std::smatch res;
					struct tm tmp = { 0 };
					//command* add_node_key_command
					//command* update_node_key_command;
					switch (flag)
					{
					case 1:
						command_time = time(0) - (3 * 3600);

						std::cout << "Pls input" << std::endl << "id_member(int)" << std::endl << "name(string)" << std::endl << "surname(string)"
							<< std::endl << "patronymic(string)" << std::endl << "data of birthday(DD.MM.YEAR)"
							<< std::endl << "resume(string)" << std::endl << "id_hr_manager(int)" << std::endl << "id_contest(int)"
							<< std::endl << "prog_lang(string)" << std::endl << "tasks_count(int)" << std::endl << "tasks_complete(int)"
							<< std::endl << "cheating(bool)" << std::endl;

						std::cin >> input;
						try {
							id_member = std::stoi(input);
						}
						catch (std::invalid_argument& e) {
							std::cerr << e.what() << std::endl;
						}
						//name
						std::cin >> input;
						name = str_p->get_str(input);
						//surname
						std::cin >> input;
						surname = str_p->get_str(input);
						//third name
						std::cin >> input;
						patronymic = str_p->get_str(input);
						//date of birthday
						std::cin >> input;
						if (std::regex_match(input, res, rgx_data)) {
							day = std::stoi(res[2].str());
							month = (std::stoi(res[3].str()) - 1);
							year = (std::stoi(res[4].str()) - 1900);
							if (month == 1 and day > 29) {
								std::cout << "Wrong day" << std::endl;
							}
							if (month % 2 == 0 and month != 1 and month != 6 and day == 31) {
								std::cout << "Wrong day" << std::endl;
							}
						}
						else {
							std::cout << "Wrong input" << std::endl;
						}
						day_of_birthday = str_p->get_str(input);
						std::cin >> input;
						resume = str_p->get_str(input);
						std::cin >> input;
						try {
							id_hrmanager = std::stoi(input);
						}
						catch (std::invalid_argument& e) {
							std::cerr << e.what() << std::endl;
						}
						std::cin >> input;
						try {
							id_contest = std::stoi(input);
						}
						catch (std::invalid_argument& e) {
							std::cerr << e.what() << std::endl;
						}
						std::cin >> input;
						prog_lang = str_p->get_str(input);

						std::cin >> input;
						try {
							tasks_count = std::stoi(input);
						}
						catch (std::invalid_argument& e) {
							std::cerr << e.what() << std::endl;
						}
						std::cin >> input;
						try {
							tasks_complete = std::stoi(input);
						}
						catch (std::invalid_argument& e) {
							std::cerr << e.what() << std::endl;
						}
						std::cin >> input;
						if (input == "true") {
							cheating = true;
						}
						else if (input == "false") {
							cheating = false;
						}
						else {
							std::cout << "Wrong input in file" << std::endl;
						}
						//contest_info* member = new contest_info(id_member, name, surname, patronymic, day_of_birthday,
						//	resume, id_hrmanager, id_contest, prog_lang, tasks_count, tasks_complete,
						//	cheating);
						////command* add_node_key_command = new add_node_key(member, collection, command_time);
						//command* add_node_key_command;
						//add_node_key_command = new add_node_key(member, vec_coll[0], command_time);
						//try {
						//	member = vec_coll[0]->find(member);
						//}
						//catch (std::invalid_argument& e) {
						//	my_invoker.set_command(add_node_key_command);
						//	my_invoker.invoke();
						//}
						//for (int i = 1; i < vec_coll.size(); i++) {
						//	add_node_key_command = new add_node_key(member, vec_coll[i], command_time);
						//	try {
						//		member = vec_coll[i]->find(member);
						//	}
						//	catch (std::invalid_argument& e) {
						//		my_invoker.set_command(add_node_key_command);
						//		my_invoker.invoke();
						//	}
						//}
						//try {
						//	my_invoker.add_command(*member, add_node_key_command);
						//}
						//catch (std::invalid_argument& e) {
						//	std::cerr << e.what() << std::endl;
						//}
						break;
					case 2:
						command_time = time(0) - (3 * 3600);
						//contest_info key;
						if (flag_key == 1) {
							std::cout << "Please, input the key:" << std::endl << "'int'" << std::endl << "'int'" << std::endl;
							int first_key;
							int second_key;
							std::cin >> input;
							try {
								first_key = std::stoi(input);
							}
							catch (std::invalid_argument& e) {
								std::cerr << e.what() << std::endl;
							}
							std::cin >> input;
							try {
								second_key = std::stoi(input);
							}
							catch (std::invalid_argument& e) {
								std::cerr << e.what() << std::endl;
							}
							//key.set_id_member(first_key);
							//key.set_id_contest(second_key);
						}
						else if (flag_key == 2) {
							std::string key;
							std::cout << "Please, input the key('string')" << std::endl;
							std::cin >> input;
							const std::string* key_resume = str_p->get_str(input);
							//key.set_resume(key_resume)
						}
						std::cout << "What field do you want to swap?" << std::endl;
						std::cout << "1. Name" << std::endl;
						std::cout << "2. Surname" << std::endl;
						std::cout << "3. Patronymic" << std::endl;
						std::cout << "4. Day of birthday" << std::endl;
						std::cout << "5. Id hr manager" << std::endl;
						std::cout << "6. Programing language" << std::endl;
						std::cout << "7. Tasks count" << std::endl;
						std::cout << "8. Tasks complete" << std::endl;
						std::cout << "9. Cheating" << std::endl;
						std::cin >> flag;
						switch (flag) {
						case 1:
							std::cin >> input;
							name = str_p->get_str(input);
							//update_node_key_command = new update_node_key_id_member(value, command_time);
							break;
						case 2:
							std::cin >> input;
							surname = str_p->get_str(input);
							//update_node_key_command = new update_node_key_id_member(value, command_time);
							break;
						case 3:
							std::cin >> input;
							patronymic = str_p->get_str(input);
							//update_node_key_command = new update_node_key_id_member(value, command_time);
							break;
						case 4:
							std::cin >> input;
							if (std::regex_match(input, res, rgx_data)) {
								day = std::stoi(res[2].str());
								month = (std::stoi(res[3].str()) - 1);
								year = (std::stoi(res[4].str()) - 1900);
								if (month == 1 and day > 29) {
									std::cout << "Wrong day" << std::endl;
								}
								if (month % 2 == 0 and month != 1 and month != 6 and day == 31) {
									std::cout << "Wrong day" << std::endl;
								}
							}
							else {
								std::cout << "Wrong input" << std::endl;
							}
							day_of_birthday = str_p->get_str(input);
							//update_node_key_command = new update_node_key_id_member(value, command_time);
							break;
						case 5:
							std::cin >> input;
							try {
								id_hrmanager = std::stoi(input);
							}
							catch (std::invalid_argument& e) {
								std::cerr << e.what() << std::endl;
							}
							//update_node_key_command = new update_node_key_id_member(value, command_time);
							break;
						case 6:
							std::cin >> input;
							prog_lang = str_p->get_str(input);
							//update_node_key_command = new update_node_key_id_member(value, command_time);
							break;
						case 7:
							std::cin >> input;
							try {
								tasks_count = std::stoi(input);
							}
							catch (std::invalid_argument& e) {
								std::cerr << e.what() << std::endl;
							}
							//update_node_key_command = new update_node_key_id_member(value, command_time);
							break;
						case 8:
							std::cin >> input;
							try {
								tasks_complete = std::stoi(input);
							}
							catch (std::invalid_argument& e) {
								std::cerr << e.what() << std::endl;
							}
							//update_node_key_command = new update_node_key_id_member(value, command_time);
							break;
						case 9:
							std::cin >> input;
							if (input == "true") {
								cheating = true;
							}
							else if (input == "false") {
								cheating = false;
							}
							else {
								std::cout << "Wrong input. It's can be only true or false" << std::endl;
							}
							//update_node_key_command = new update_node_key_id_member(value, command_time);
							break;
						default:
							break;
						}
						//add command to contest_info
						break;
					case 3:
						command_time = time(0) - (3 * 3600);
						//contest_info key;
						if (flag_key == 1) {
							std::cout << "Please, input the key:" << std::endl << "'int'" << std::endl << "'int'" << std::endl;
							int first_key;
							int second_key;
							std::cin >> input;
							try {
								first_key = std::stoi(input);
							}
							catch (std::invalid_argument& e) {
								std::cerr << e.what() << std::endl;
							}
							std::cin >> input;
							try {
								second_key = std::stoi(input);
							}
							catch (std::invalid_argument& e) {
								std::cerr << e.what() << std::endl;
							}
							//key.set_id_member(first_key);
							//key.set_id_contest(second_key);
						}
						else if (flag_key == 2) {
							std::string key;
							std::cout << "Please, input the key('string')" << std::endl;
							std::cin >> input;
							const std::string* key_resume = str_p->get_str(input);
							//key.set_resume(key_resume)
						}
						//get contest_info from collection
						/*contest_info* member;
						for (int i = 0; i < vec_coll.size(); i++) {
							command* remove_node_key_command = new remove_node_key(&key, vec_coll[i], command_time);
							try {
								member = d_base.go_to_contest_info(vec_coll[i], &key);
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
						try {
							member = d_base.go_to_contest_info(collection, &key);
						}
						catch (std::invalid_argument& e) {
							std::cerr << e.what();
						}*/
						break;
					case 4:
						command_time = time(0);
						//contest_info key;
						if (flag_key == 1) {
							std::cout << "Please, input the key:" << std::endl << "'int'" << std::endl << "'int'" << std::endl;
							int first_key;
							int second_key;
							std::cin >> input;
							try {
								first_key = std::stoi(input);
							}
							catch (std::invalid_argument& e) {
								std::cerr << e.what() << std::endl;
							}
							std::cin >> input;
							try {
								second_key = std::stoi(input);
							}
							catch (std::invalid_argument& e) {
								std::cerr << e.what() << std::endl;
							}
							//key.set_id_member(first_key);
							//key.set_id_contest(second_key);
						}
						else if (flag_key == 2) {
							std::string key;
							std::cout << "Please, input the key('string')" << std::endl;
							std::cin >> input;
							const std::string* key_resume = str_p->get_str(input);
							//key.set_resume(key_resume)
						}
						std::cout << "Please, input time (HH:MM:SS-DD.MM.YYYY) You can only input 2023" << std::endl;
						std::cin >> input;
						if (std::regex_match(input, res, rgx)) {
							tmp = *localtime(&command_time);
							tmp.tm_hour = hour = (std::stoi(res[2].str()) - 3);
							tmp.tm_min = minute = std::stoi(res[5].str());
							tmp.tm_sec = seconds = std::stoi(res[6].str());
							day = std::stoi(res[7].str());
							month = (std::stoi(res[8].str()) - 1);
							year = (std::stoi(res[9].str()) - 1900);
							if (year != (2023 - 1900)) {
								std::cout << "Wrong year" << std::endl;
							}
							if (month == 1 and day > 28) {
								std::cout << "Wrong day" << std::endl;
							}
							if (month % 2 == 0 and month != 1 and month != 6 and day == 31) {
								std::cout << "Wrong day" << std::endl;
							}
							tmp.tm_mday = day;
							tmp.tm_mon = month;
							tmp.tm_year = year;
							input_time = mktime(&tmp);
						}
						else {
							std::cout << "Wrong input time" << std::endl;
						}
						/*command* read_node_key_command = new read_node_key(&key, collection, input_time);
						my_invoker.set_command(read_node_key_command);
						try {
							my_invoker.invoke();
						}
						catch (std::invalid_argument& e) {
							std::cerr << e.what() << std::endl;
						}*/
						break;
					case 5:
						command_time = time(0);
						//contest_info key1;
						//contest_info key2;
						if (flag_key == 1) {
							std::cout << "Please, input the first key:" << std::endl << "'int'" << std::endl << "'int'" << std::endl;
							int first_first_key;
							int first_second_key;
							int second_first_key;
							int second_second_key;
							std::cin >> input;
							try {
								first_first_key = std::stoi(input);
							}
							catch (std::invalid_argument& e) {
								std::cerr << e.what() << std::endl;
							}
							std::cin >> input;
							try {
								first_second_key = std::stoi(input);
							}
							catch (std::invalid_argument& e) {
								std::cerr << e.what() << std::endl;
							}
							std::cout << "Please, input the second key:" << std::endl << "'int'" << std::endl << "'int'" << std::endl;
							std::cin >> input;
							try {
								second_first_key = std::stoi(input);
							}
							catch (std::invalid_argument& e) {
								std::cerr << e.what() << std::endl;
							}
							std::cin >> input;
							try {
								second_second_key = std::stoi(input);
							}
							catch (std::invalid_argument& e) {
								std::cerr << e.what() << std::endl;
							}
							//key.set_id_member(first_key);
							//key.set_id_contest(second_key);
						}
						else if (flag_key == 2) {
							std::string key1;
							std::string key2;
							std::cout << "Please, input the first key('string')" << std::endl;
							std::cin >> input;
							const std::string* key1_resume = str_p->get_str(input);
							std::cout << "Please, input the first key('string')" << std::endl;
							std::cin >> input;
							const std::string* key2_resume = str_p->get_str(input);
							//key1.set_resume(key1_resume)
							//key2.set_resume(key2_resume)
						}
						std::cout << "Please, input time (HH:MM:SS-DD.MM.YYYY) You can only input 2023" << std::endl;
						std::cin >> input;
						if (std::regex_match(input, res, rgx)) {
							tmp = *localtime(&command_time);
							tmp.tm_hour = hour = (std::stoi(res[2].str()) - 3);
							tmp.tm_min = minute = std::stoi(res[5].str());
							tmp.tm_sec = seconds = std::stoi(res[6].str());
							day = std::stoi(res[7].str());
							month = (std::stoi(res[8].str()) - 1);
							year = (std::stoi(res[9].str()) - 1900);
							if (year != (2023 - 1900)) {
								std::cout << "Wrong year" << std::endl;
							}
							if (month == 1 and day > 28) {
								std::cout << "Wrong day" << std::endl;
							}
							if (month % 2 == 0 and month != 1 and month != 6 and day == 31) {
								std::cout << "Wrong day" << std::endl;
							}
							tmp.tm_mday = day;
							tmp.tm_mon = month;
							tmp.tm_year = year;
							input_time = mktime(&tmp);
						}
						else {
							std::cout << "Wrong input time" << std::endl;
						}
						/*command* read_node_keys_command = new read_node_keys(&key1, &key2, collection, input_time, flag_tree);
						my_invoker.set_command(read_node_keys_command);
						my_invoker.invoke();*/

						break;
					default:
						break;
					}
					/*std::cout << "Please input id_member and id_contest like 'number' 'number'" << std::endl;
					int id_member, id_contest;
					std::cin >> id_member >> id_contest;*/
				}
			case 10:
				//saving Data Base
				break;
			case 11:
				std::cout << "Program is end" << std::endl;
				break;
			default:
				throw std::invalid_argument("Wrong choice");
			}
		}
	}
	else if (flag == 2) {
		std::string buffer;
		std::cin >> buffer;
		std::ifstream file(buffer);
		if (!file.is_open()) {
			std::cout << "File is not opened" << std::endl;
			file.close();
			throw std::invalid_argument("don't open the file");
		}
		// code from main
	}
}