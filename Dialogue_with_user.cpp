#include "Dialogue_with_user.h"

void dialogue::dialogue_user(int argc, char* argv[]) {
	int flag;
	bool flag_dbase = false;

	string_pool* str_p = string_pool::Instance();

	data_base* d_base = nullptr;

	dbase_safe saver;

	data_base::flag flag_tree;

	int b_const = 3;

	std::string path_file = "C:\\savebd\\savetree.txt";

	while (true) {
		std::cout << "Do you want upload tree or do new?" << std::endl << "1. Yes" << std::endl << "2. No" << std::endl;

		std::cin >> flag;

		if (flag == 1) {
			// upload
			//std::cout << "Please input path to file with Data Base" << std::endl;
			dbase_safe saver(path_file, d_base, data_base::flag::Btree);
			try {
				d_base = saver.restore(flag_tree);
			}
			catch (std::invalid_argument& e) {
				std::cerr << e.what() << std::endl;
				
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());

				goto input_file;
			}
			flag_dbase = true;
			break;
		}
		else if (flag == 2) {
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			break;
		}
		else {
			std::cerr << "Wrong number" << std::endl;

			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());

			goto input_file;
		}
		
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());

		input_file:;
	}
	while (true) {

		std::cout << "Choose how you want to input?" << std::endl << "1. With console" << std::endl << "2. With file" << std::endl;

		std::cin >> flag;

		if (flag == 1 or flag == 2) {
			break;
		}
		
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
	console:;
	}
	//data_base d_base;
	const std::string* nameofpull;
	const std::string* nameofscheme;
	const std::string* nameofcollection;

	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	if (flag == 1) {

		while (true) {
			std::cout << "Now you can choose what commands you want to do" << std::endl << "1. Create dbase" << std::endl
				<< "2. Create pool" << std::endl << "3. Create scheme" << std::endl << "4. Create collection" << std::endl << "5. Delete dbase" << std::endl
				<< "6. Delete pool" << std::endl << "7. Delete scheme" << std::endl << "8. Delete collection" << std::endl << "9. Commands collection" << std::endl
				<< "10. Save data base" << std::endl << "11. End program" << std::endl;
			std::cin >> flag;

			std::string input_name;

			if (flag == 11) {
				break;
			}
			switch (flag) {
			case 1:
				if (d_base != nullptr) {
					std::cout << "Data base already exist" << std::endl;
				}
				else {
					// create dbase
					std::cout << "Now we need to create data base. Choose what tree will be data base." << std::endl
						<< "1. B-tree" << std::endl << "2. AVL tree" << std::endl << "3. Splay tree" << std::endl;

					std::cin >> flag;
					switch (flag) {
					case 1:
						while (true) {
							std::cout << "Please, input const for Btree" << std::endl;

							std::cin >> b_const;

							if (b_const > 2) {
								break;
							}

							std::cin.clear();
							std::cin.ignore(std::cin.rdbuf()->in_avail());

						}
						

						try {
							d_base = new data_base(data_base::flag::Btree, 3);
						}
						catch (std::invalid_argument& e) {
							std::cerr << e.what() << std::endl;
							
							std::cin.clear();
							std::cin.ignore(std::cin.rdbuf()->in_avail());

							goto common_commands;
						}
						flag_tree = data_base::flag::Btree;
						//create tree
						break;
					case 2:
						//create tree

						try {
							d_base = new data_base(data_base::flag::AVL);
						}
						catch (std::invalid_argument& e) {
							std::cerr << e.what() << std::endl;

							std::cin.clear();
							std::cin.ignore(std::cin.rdbuf()->in_avail());

							goto common_commands;
						}
						flag_tree = data_base::flag::AVL;
						break;
					case 3:
						//create tree

						try {
							d_base = new data_base(data_base::flag::Splay);
						}
						catch (std::invalid_argument& e) {
							std::cerr << e.what() << std::endl;

							std::cin.clear();
							std::cin.ignore(std::cin.rdbuf()->in_avail());

							goto common_commands;
						}
						flag_tree = data_base::flag::Splay;
						break;
					default:
						std::cout << "Wrong input tree" << std::endl;

						std::cin.clear();
						std::cin.ignore(std::cin.rdbuf()->in_avail());

						goto common_commands;
					}
					flag_dbase = true;
				}
				break;
			case 2:
				if (d_base == nullptr) {
					std::cout << "Data Base is not exist, you can't do any commands" << std::endl;
					goto common_commands;
				}

				std::cout << "Now you are creating pool." << std::endl;

				std::cout << "Pls input name of pull" << std::endl;

				std::cin >> input_name;
				nameofpull = str_p->get_str(input_name);

				try {
					d_base->create_pull(nameofpull, data_base::flag::Btree, 3);
				}
				catch (std::invalid_argument& e) {
					std::cerr << e.what() << std::endl;
						
					std::cin.clear();
					std::cin.ignore(std::cin.rdbuf()->in_avail());

					goto common_commands;
				}
				break;
				
			case 3:

				if (d_base == nullptr) {
					std::cout << "Data Base is not exist, you can't do any commands" << std::endl;
					goto common_commands;
				}

				std::cout << "Now you are creating scheme." << std::endl;

				std::cout << "Pls input name of pull and name of scheme" << std::endl;
				std::cin >> input_name;
				nameofpull = str_p->get_str(input_name);
				std::cin >> input_name;
				nameofscheme = str_p->get_str(input_name);
				try {
					d_base->create_scheme(nameofscheme, nameofpull, data_base::flag::Btree);
				}
				catch (std::invalid_argument& e) {
					std::cerr << e.what() << std::endl;
						
					std::cin.clear();
					std::cin.ignore(std::cin.rdbuf()->in_avail());

					goto common_commands;
				}
				break;

			case 4:

				if (d_base == nullptr) {
					std::cout << "Data Base is not exist, you can't do any commands" << std::endl;
					goto common_commands;
				}

				std::cout << "Now you are creating collection." << std::endl;

				std::cout << "Pls input name of pull, name of scheme and name of collection" << std::endl;

				std::cin >> input_name;
				nameofpull = str_p->get_str(input_name);
				std::cin >> input_name;
				nameofscheme = str_p->get_str(input_name);
				std::cin >> input_name;
				nameofcollection = str_p->get_str(input_name);
				
				try {
					d_base->create_collection(nameofcollection, nameofpull, nameofscheme, data_base::flag::Btree, 3);
				}
				catch (std::invalid_argument& e) {
					std::cerr << e.what() << std::endl;
						
					std::cin.clear();
					std::cin.ignore(std::cin.rdbuf()->in_avail());

					goto common_commands;
				}
				break;

			case 5:
				try {
					if (d_base == nullptr) {
						std::cout << "Data base is not exist" << std::endl;
						
						std::cin.clear();
						std::cin.ignore(std::cin.rdbuf()->in_avail());

						goto common_commands;
					}
					d_base->~data_base();
				}
				catch (std::invalid_argument& e) {
					std::cerr << e.what() << std::endl;
					
					std::cin.clear();
					std::cin.ignore(std::cin.rdbuf()->in_avail());

					goto common_commands;
				}
				break;
			case 6:
				std::cout << "Now you are deleting pool." << std::endl;

				std::cout << "Pls input name of pull" << std::endl;

				if (d_base == nullptr) {
					std::cout << "Data base is not exist" << std::endl;
					
					std::cin.clear();
					std::cin.ignore(std::cin.rdbuf()->in_avail());

					goto common_commands;
				}

				std::cin >> input_name;
				nameofpull = str_p->get_str(input_name);
				try {
					d_base->delete_pull(nameofpull);
				}
				catch (std::invalid_argument& e) {
					std::cerr << e.what() << std::endl;
					
					std::cin.clear();
					std::cin.ignore(std::cin.rdbuf()->in_avail());

					goto common_commands;
				}
				break;
			case 7:
				std::cout << "Now you are deleting scheme." << std::endl;

				std::cout << "Pls input name of pull and name of scheme" << std::endl;

				if (d_base == nullptr) {
					std::cout << "Data base is not exist" << std::endl;
					
					std::cin.clear();
					std::cin.ignore(std::cin.rdbuf()->in_avail());

					goto common_commands;
				}

				std::cin >> input_name;
				nameofpull = str_p->get_str(input_name);
				std::cin >> input_name;
				nameofscheme = str_p->get_str(input_name);

				try {
					d_base->delete_scheme(nameofscheme, nameofpull);
				}
				catch (std::invalid_argument& e) {
					std::cerr << e.what() << std::endl;
					
					std::cin.clear();
					std::cin.ignore(std::cin.rdbuf()->in_avail());

					goto common_commands;
				}
				break;
			case 8:
				std::cout << "Now you are deleting collection." << std::endl;

				std::cout << "Pls input name of pull, name of scheme and name of collection" << std::endl;

				if (d_base == nullptr) {
					std::cout << "Data base is not exist" << std::endl;
					
					std::cin.clear();
					std::cin.ignore(std::cin.rdbuf()->in_avail());

					goto common_commands;
				}

				std::cin >> input_name;
				nameofpull = str_p->get_str(input_name);
				std::cin >> input_name;
				nameofscheme = str_p->get_str(input_name);
				std::cin >> input_name;
				nameofcollection = str_p->get_str(input_name);
				try {
					d_base->delete_collection(nameofcollection, nameofpull, nameofscheme);
				}
				catch (std::invalid_argument& e) {
					std::cerr << e.what() << std::endl;
					
					std::cin.clear();
					std::cin.ignore(std::cin.rdbuf()->in_avail());

					goto common_commands;
				}
				break;
			case 9:
				while (true) {
					if (d_base == nullptr) {
						std::cout << "Data Base is not exist, you can't do any commands" << std::endl;
						goto common_commands;
					}
					std::cout << "You need to write 'name of pool' 'name of scheme' 'name of collection'" << std::endl;
					std::cin >> input_name;
					nameofpull = str_p->get_str(input_name);
					std::cin >> input_name;
					nameofscheme = str_p->get_str(input_name);
					std::cin >> input_name;
					nameofcollection = str_p->get_str(input_name);
					int flag_key;

					std::vector<collection*> vec_coll;
					collection* collection;
					try {
						vec_coll = d_base->go_to_collection(nameofpull, nameofscheme, nameofcollection);
					}
					catch (std::invalid_argument& e) {
						std::cerr << e.what() << std::endl;

						std::cin.clear();
						std::cin.ignore(std::cin.rdbuf()->in_avail());

						goto common_commands;
					}
					while (true) {

						std::cout << "Now you can choose key what you want." << std::endl << "1. default key(id_member, id_contest)" << std::endl
							<< "2. resume key" << std::endl;

						std::cin >> flag_key;

						
						// can add cycle for this collection

						if (flag_key == 1) {
							collection = vec_coll[0];
							break;
						}
						else if (flag_key == 2) {
							collection = vec_coll[1];
							break;
						}
						else {
							std::cout << "Wrong flag" << std::endl;

							std::cin.clear();
							std::cin.ignore(std::cin.rdbuf()->in_avail());

							goto choice_key;
						}
						choice_key:;
					}

					std::time_t command_time;
					time_t input_time;
					
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
					
					command* add_node_key_command;
					command* update_node_key_command;
					
					invoker my_invoker;

					contest_info key_add;

					contest_info key_remove;
					contest_info key_read;

					contest_info key1_read;
					contest_info key2_read;

					
					while (true) {

						std::cout << "Choose command." << std::endl << "1. Add contest (add_node_key)" << std::endl << "2. Update contest (update_node_key)"
							<< std::endl << "3. Remove contest (remove_node_key)" << std::endl << "4. Read contest (read_node_key)" << std::endl <<
							"5. Read contests (read_nodes_key)" << std::endl << "6. End input commands" << std::endl;
						std::cin >> flag;

						if (flag == 6) {
							
							std::cin.clear();
							std::cin.ignore(std::cin.rdbuf()->in_avail());

							break;
						}

						std::cin.clear();
						std::cin.ignore(std::cin.rdbuf()->in_avail());

						switch (flag)
						{
						case 1:
							command_time = time(0);

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
								
								std::cin.clear();
								std::cin.ignore(std::cin.rdbuf()->in_avail());

								goto end_commands;
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
								std::cout << std::endl;
								day = std::stoi(res[1].str());
								month = (std::stoi(res[2].str()) - 1);
								year = (std::stoi(res[3].str()) - 1900);
								if (month == 1 and day > 28 and year % 4 != 0 and year != 0) {
									std::cout << "Wrong day" << std::endl;
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
								if (year % 4 == 0 and day != 29) {
									std::cout << "Wrond data" << std::endl;
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
								if (month % 2 == 0 and month != 1 and month != 6 and day == 31) {
									std::cout << "Wrong day" << std::endl;
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
							}
							else {
								std::cout << "Wrong input" << std::endl;
								
								std::cin.clear();
								std::cin.ignore(std::cin.rdbuf()->in_avail());

								goto end_commands;
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
								
								std::cin.clear();
								std::cin.ignore(std::cin.rdbuf()->in_avail());

								goto end_commands;
							}
							std::cin >> input;
							try {
								id_contest = std::stoi(input);
							}
							catch (std::invalid_argument& e) {
								std::cerr << e.what() << std::endl;
								
								std::cin.clear();
								std::cin.ignore(std::cin.rdbuf()->in_avail());

								goto end_commands;
							}
							std::cin >> input;
							prog_lang = str_p->get_str(input);

							std::cin >> input;
							try {
								tasks_count = std::stoi(input);
							}
							catch (std::invalid_argument& e) {
								std::cerr << e.what() << std::endl;
								
								std::cin.clear();
								std::cin.ignore(std::cin.rdbuf()->in_avail());

								goto end_commands;
							}
							std::cin >> input;
							try {
								tasks_complete = std::stoi(input);
							}
							catch (std::invalid_argument& e) {
								std::cerr << e.what() << std::endl;
								
								std::cin.clear();
								std::cin.ignore(std::cin.rdbuf()->in_avail());

								goto end_commands;
							}
							std::cin >> input;
							if (input == "true") {
								cheating = true;
							}
							else if (input == "false") {
								cheating = false;
							}
							else {
								std::cout << "Wrong input cheating" << std::endl;
								
								std::cin.clear();
								std::cin.ignore(std::cin.rdbuf()->in_avail());

								goto end_commands;
							}

							if (tasks_complete > tasks_count) {
								std::cout << "Problem with tasks" << std::endl;

								goto end_commands;
							}

							contest_info* member;
							member = new contest_info(id_member, name, surname, patronymic, day_of_birthday,
								resume, id_hrmanager, id_contest, prog_lang, tasks_count, tasks_complete,
								cheating);

							command* add_node_key_command;
							add_node_key_command = new add_node_key(member, vec_coll[0], command_time);
							try {
								member = vec_coll[0]->find(member);
							}
							catch (std::invalid_argument& e) {
								my_invoker.set_command(add_node_key_command);
								try {
									my_invoker.invoke();
								}
								catch (std::invalid_argument& e) {
									std::cerr << e.what() << std::endl;
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
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
								
								std::cin.clear();
								std::cin.ignore(std::cin.rdbuf()->in_avail());

								goto end_commands;
							}
							
							std::cin.clear();
							std::cin.ignore(std::cin.rdbuf()->in_avail());

							break;
						case 2:
							command_time = time(0);

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
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
								std::cin >> input;
								try {
									second_key = std::stoi(input);
								}
								catch (std::invalid_argument& e) {
									std::cerr << e.what() << std::endl;
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
								key_add.set_id_member(first_key);
								key_add.set_id_contest(second_key);
							}
							else if (flag_key == 2) {
								std::cout << "Please, input the key('string')" << std::endl;
								std::cin >> input;
								const std::string* key_resume = str_p->get_str(input);
								key_add.set_resume(key_resume);
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
								update_node_key_command = new update_node_key_name(name, command_time);
								break;
							case 2:
								std::cin >> input;
								surname = str_p->get_str(input);
								update_node_key_command = new update_node_key_surname(surname, command_time);
								break;
							case 3:
								std::cin >> input;
								patronymic = str_p->get_str(input);
								update_node_key_command = new update_node_key_patronymic(patronymic, command_time);
								break;
							case 4:
								std::cin >> input;
								if (std::regex_match(input, res, rgx_data)) {
									day = std::stoi(res[1].str());
									month = (std::stoi(res[2].str()) - 1);
									year = (std::stoi(res[3].str()) - 1900);
									if (month == 1 and day > 28 and year % 4 != 0 and year != 0) {
										std::cout << "Wrong day" << std::endl;
										
										std::cin.clear();
										std::cin.ignore(std::cin.rdbuf()->in_avail());

										goto end_commands;
									}
									if (year % 4 == 0 and day != 29) {
										std::cout << "Wrond data" << std::endl;
										
										std::cin.clear();
										std::cin.ignore(std::cin.rdbuf()->in_avail());

										goto end_commands;
									}
									if (month % 2 == 0 and month != 1 and month != 6 and day == 31) {
										std::cout << "Wrong day" << std::endl;
										
										std::cin.clear();
										std::cin.ignore(std::cin.rdbuf()->in_avail());

										goto end_commands;
									}
								}
								else {
									std::cout << "Wrong input" << std::endl;
								}
								day_of_birthday = str_p->get_str(input);
								update_node_key_command = new update_node_key_day_of_birthday(day_of_birthday, command_time);
								break;
							case 5:
								std::cin >> input;
								try {
									id_hrmanager = std::stoi(input);
								}
								catch (std::invalid_argument& e) {
									std::cerr << e.what() << std::endl;
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
								update_node_key_command = new update_node_key_id_hrmanager(id_hrmanager, command_time);
								break;
							case 6:
								std::cin >> input;
								prog_lang = str_p->get_str(input);
								update_node_key_command = new update_node_key_prog_lang(prog_lang, command_time);
								break;
							case 7:
								std::cin >> input;
								try {
									tasks_count = std::stoi(input);
								}
								catch (std::invalid_argument& e) {
									std::cerr << e.what() << std::endl;
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
								update_node_key_command = new update_node_key_tasks_count(tasks_count, command_time);
								break;
							case 8:
								std::cin >> input;
								try {
									tasks_complete = std::stoi(input);
								}
								catch (std::invalid_argument& e) {
									std::cerr << e.what() << std::endl;
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
								update_node_key_command = new update_node_key_tasks_complete(tasks_complete, command_time);
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
									goto end_commands;
								}
								update_node_key_command = new update_node_key_cheating(cheating, command_time);
								break;
							default:
								std::cout << "Wrong update" << std::endl;
								
								std::cin.clear();
								std::cin.ignore(std::cin.rdbuf()->in_avail());

								goto end_commands;
								break;
							}
							//add command to contest_info
							if (flag_key == 1) {
								comparer_id_member_id_contest _comp;
								if (dynamic_cast<Btree<contest_info*, contest_info*, comparer_id_member_id_contest>*>((collection_default*)vec_coll[flag_key-1])) {
									Btree<contest_info*, contest_info*, comparer_id_member_id_contest>* _btree =
										dynamic_cast<Btree<contest_info*, contest_info*, comparer_id_member_id_contest>*>((collection_default*)vec_coll[flag_key-1]);
									command* temp;
									contest_info copy_value;
									auto it = _btree->infix_iterator_begin();
									for (it; it != _btree->infix_iterator_end(); ++it) {
										if (_comp.comparate(std::get<0>(*it), &key_add) == 0) {
											try {
												my_invoker.add_command(*std::get<1>(*it), update_node_key_command);
											}
											catch (std::invalid_argument& e) {
												std::cerr << e.what() << std::endl;

												std::cin.clear();
												std::cin.ignore(std::cin.rdbuf()->in_avail());

												goto end_commands;
											}
											break;
										}
									}
								}
								else if (dynamic_cast<binary_search_tree<contest_info*, contest_info*, comparer_id_member_id_contest>*>((collection_default*)vec_coll[flag_key-1])) {
									binary_search_tree<contest_info*, contest_info*, comparer_id_member_id_contest>* _btree =
										dynamic_cast<binary_search_tree<contest_info*, contest_info*, comparer_id_member_id_contest>*>((collection_default*)vec_coll[flag_key-1]);
									command* temp;
									contest_info copy_value;
									auto it = _btree->infix_iterator_begin();
									for (it; it != _btree->infix_iterator_end(); ++it) {
										if (_comp.comparate(std::get<0>(*it), &key_add) == 0) {
											try {
												my_invoker.add_command(*std::get<1>(*it), update_node_key_command);
											}
											catch (std::invalid_argument& e) {
												std::cerr << e.what() << std::endl;

												std::cin.clear();
												std::cin.ignore(std::cin.rdbuf()->in_avail());

												goto end_commands;
											}
											break;
										}
									}
								}
							}
							else if (flag_key == 2) {
								comparer_resume _comp_resume;
								if (dynamic_cast<Btree<contest_info*, contest_info*, comparer_resume>*>((collection_resume*)vec_coll[flag_key])) {
									Btree<contest_info*, contest_info*, comparer_resume>* _btree =
										dynamic_cast<Btree<contest_info*, contest_info*, comparer_resume>*>((collection_default*)vec_coll[flag_key]);
									command* temp;
									contest_info copy_value;
									auto it = _btree->infix_iterator_begin();
									for (it; it != _btree->infix_iterator_end(); ++it) {
										if (_comp_resume.comparate(std::get<0>(*it), &key_add) == 0) {
											try {
												my_invoker.add_command(*std::get<1>(*it), update_node_key_command);
											}
											catch (std::invalid_argument& e) {
												std::cerr << e.what() << std::endl;
												
												std::cin.clear();
												std::cin.ignore(std::cin.rdbuf()->in_avail());

												goto end_commands;
											}
											break;
										}
									}
								}
								else if (dynamic_cast<binary_search_tree<contest_info*, contest_info*, comparer_id_member_id_contest>*>((collection_default*)vec_coll[flag_key])) {
									binary_search_tree<contest_info*, contest_info*, comparer_id_member_id_contest>* _btree =
										dynamic_cast<binary_search_tree<contest_info*, contest_info*, comparer_id_member_id_contest>*>((collection_default*)vec_coll[flag_key]);
									command* temp;
									contest_info copy_value;
									auto it = _btree->infix_iterator_begin();
									for (it; it != _btree->infix_iterator_end(); ++it) {
										if (_comp_resume.comparate(std::get<0>(*it), &key_add) == 0) {
											try {
												my_invoker.add_command(*std::get<1>(*it), update_node_key_command);
											}
											catch (std::invalid_argument& e) {
												std::cerr << e.what() << std::endl;

												std::cin.clear();
												std::cin.ignore(std::cin.rdbuf()->in_avail());

												goto end_commands;
											}
											break;
										}
									}
								}
							}
							else {
								std::cout << "Wrong tree" << std::endl;
								
								std::cin.clear();
								std::cin.ignore(std::cin.rdbuf()->in_avail());

								goto end_commands;
							}
							break;
						case 3:
							command_time = time(0);

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
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
								std::cin >> input;
								try {
									second_key = std::stoi(input);
								}
								catch (std::invalid_argument& e) {
									std::cerr << e.what() << std::endl;
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
								key_remove.set_id_member(first_key);
								key_remove.set_id_contest(second_key);
							}
							else if (flag_key == 2) {
								std::cout << "Please, input the key('string')" << std::endl;
								std::cin >> input;
								const std::string* key_resume = str_p->get_str(input);
								key_remove.set_resume(key_resume);
							}
							//get contest_info from collection
							contest_info* member_remove;
							for (int i = 0; i < vec_coll.size(); i++) {
								command* remove_node_key_command = new remove_node_key(&key_remove, vec_coll[i], command_time);
								try {
									member_remove = d_base->go_to_contest_info(vec_coll[i], &key_remove);
								}
								catch (std::invalid_argument& e) {
									std::cerr << e.what() << std::endl;
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
								try {
									my_invoker.add_command(*member_remove, remove_node_key_command);
								}
								catch (std::invalid_argument& e) {
									std::cerr << e.what() << std::endl;
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
							}
							try {
								member_remove = d_base->go_to_contest_info(collection, &key_remove);
							}
							catch (std::invalid_argument& e) {
								std::cerr << e.what() << std::endl;
								
								std::cin.clear();
								std::cin.ignore(std::cin.rdbuf()->in_avail());

								goto end_commands;
							}
							break;
						case 4:
							command_time = time(0);

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
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
								std::cin >> input;
								try {
									second_key = std::stoi(input);
								}
								catch (std::invalid_argument& e) {
									std::cerr << e.what() << std::endl;
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
								key_read.set_id_member(first_key);
								key_read.set_id_contest(second_key);
							}
							else if (flag_key == 2) {
								std::cout << "Please, input the key('string')" << std::endl;
								std::cin >> input;
								const std::string* key_resume = str_p->get_str(input);
								key_read.set_resume(key_resume);
							}
							std::cout << "Please, input time (HH:MM:SS-DD.MM.YYYY)" << std::endl;
							std::cin >> input;
							if (std::regex_match(input, res, rgx)) {
								tmp = *localtime(&command_time);
								tmp.tm_hour = hour = (std::stoi(res[2].str()));
								tmp.tm_min = minute = std::stoi(res[5].str());
								tmp.tm_sec = seconds = std::stoi(res[6].str());
								day = std::stoi(res[7].str());
								month = (std::stoi(res[8].str()) - 1);
								year = (std::stoi(res[9].str()) - 1900);
								if (month == 1 and day > 28 and year % 4 != 0 and year != 0) {
									std::cout << "Wrong day" << std::endl;
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
								if (year % 4 == 0 and day != 29) {
									std::cout << "Wrond data" << std::endl;
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
								if (month % 2 == 0 and month != 1 and month != 6 and day == 31) {
									std::cout << "Wrong day" << std::endl;
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
								tmp.tm_mday = day;
								tmp.tm_mon = month;
								tmp.tm_year = year;
								input_time = mktime(&tmp);
							}
							else {
								std::cout << "Wrong time" << std::endl;
								
								std::cin.clear();
								std::cin.ignore(std::cin.rdbuf()->in_avail());

								goto end_commands;
							}
							command* read_node_key_command;
							read_node_key_command = new read_node_key(&key_read, collection, input_time);
							my_invoker.set_command(read_node_key_command);
							try {
								my_invoker.invoke();
							}
							catch (std::invalid_argument& e) {
								std::cerr << e.what() << std::endl;
								
								std::cin.clear();
								std::cin.ignore(std::cin.rdbuf()->in_avail());

								goto end_commands;
							}
							break;
						case 5:
							command_time = time(0);

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
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
								std::cin >> input;
								try {
									first_second_key = std::stoi(input);
								}
								catch (std::invalid_argument& e) {
									std::cerr << e.what() << std::endl;

									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
								std::cout << "Please, input the second key:" << std::endl << "'int'" << std::endl << "'int'" << std::endl;
								std::cin >> input;
								try {
									second_first_key = std::stoi(input);
								}
								catch (std::invalid_argument& e) {
									std::cerr << e.what() << std::endl;
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
								std::cin >> input;
								try {
									second_second_key = std::stoi(input);
								}
								catch (std::invalid_argument& e) {
									std::cerr << e.what() << std::endl;
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
								key1_read.set_id_member(first_first_key);
								key1_read.set_id_contest(first_second_key);
								key2_read.set_id_member(second_first_key);
								key2_read.set_id_contest(second_second_key);
							}
							else if (flag_key == 2) {
								std::cout << "Please, input the first key('string')" << std::endl;
								std::cin >> input;
								const std::string* key1_resume = str_p->get_str(input);
								std::cout << "Please, input the first key('string')" << std::endl;
								std::cin >> input;
								const std::string* key2_resume = str_p->get_str(input);
								key1_read.set_resume(key1_resume);
								key2_read.set_resume(key2_resume);
							}
							std::cout << "Please, input time (HH:MM:SS-DD.MM.YYYY)" << std::endl;
							std::cin >> input;
							if (std::regex_match(input, res, rgx)) {
								tmp = *localtime(&command_time);
								tmp.tm_hour = hour = (std::stoi(res[2].str()));
								tmp.tm_min = minute = std::stoi(res[5].str());
								tmp.tm_sec = seconds = std::stoi(res[6].str());
								day = std::stoi(res[7].str());
								month = (std::stoi(res[8].str()) - 1);
								year = (std::stoi(res[9].str()) - 1900);
								if (month == 1 and day > 28 and year%4 != 0 and year != 0) {
									std::cout << "Wrong day" << std::endl;
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
								if (year % 4 == 0 and day != 29) {
									std::cout << "Wrond data" << std::endl;
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
								if (month % 2 == 0 and month != 1 and month != 6 and day == 31) {
									std::cout << "Wrong day" << std::endl;
									
									std::cin.clear();
									std::cin.ignore(std::cin.rdbuf()->in_avail());

									goto end_commands;
								}
								tmp.tm_mday = day;
								tmp.tm_mon = month;
								tmp.tm_year = year;
								input_time = mktime(&tmp);
							}
							else {
								std::cout << "Wrong input time" << std::endl;
								
								std::cin.clear();
								std::cin.ignore(std::cin.rdbuf()->in_avail());

								goto end_commands;
							}
							command* read_node_keys_command;
							read_node_keys_command = new read_node_keys(&key1_read, &key1_read, collection, input_time, flag_key);
							my_invoker.set_command(read_node_keys_command);
							my_invoker.invoke();

							break;
						default:

							std::cin.clear();
							std::cin.ignore(std::cin.rdbuf()->in_avail());

							goto end_commands;
							break;
						}

						std::cin.clear();
						std::cin.ignore(std::cin.rdbuf()->in_avail());

					end_commands:;
					}
				
					/*std::cout << "Please input id_member and id_contest like 'number' 'number'" << std::endl;
					int id_member, id_contest;
					std::cin >> id_member >> id_contest;*/
				}
			case 10:
				// check for empty data base

				dialogue dl;

				

				//saving Data Base
				
				if (dl.check_save(d_base, flag_tree)) {

					saver = dbase_safe(path_file, d_base, flag_tree);
					try {
						saver.save();
					}
					catch (std::invalid_argument& e) {
						std::cerr << e.what() << std::endl;
					
						std::cin.clear();
						std::cin.ignore(std::cin.rdbuf()->in_avail());

						goto common_commands;
					}
				}
				else {
					std::cout << "You have empty elements" << std::endl;
					goto common_commands;
				}
			case 11:
				std::cout << "Program is end" << std::endl;
				
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());

				goto end_program;
			default:
				std::cout << "Wrong flag choise" << std::endl;
				
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());

				goto common_commands;
			}
		common_commands:;
		}
	}
	else if (flag == 2) {
		std::string buffer;
		std::cout << "Please, input path to file for commands" << std::endl;
		std::cin >> buffer;
		std::cout << buffer << std::endl;
		std::ifstream fin(buffer, std::ios::in);
		if (!fin.is_open()) {
			throw std::invalid_argument("File is not exist");
			fin.close();
			return;
		}
		dialogue dl;
		dl.commands_from_file(fin, d_base);
		// code from main
	}
	delete d_base;
end_program:;
}

bool dialogue::check_save(data_base* d_base, data_base::flag flag_tree) {
	if (d_base == nullptr) {
		return false;
	}
	if (flag_tree == data_base::flag::Btree) {
		auto btree = (Btree<const std::string*, pull*, string_const_ptr>*)(d_base->get_dbase());
		if (!btree->check_tree()) {
			return false;
		}
		auto it_begin = btree->infix_iterator_begin();
		

		//auto it_end = btree->infix_iterator_end();
		for (it_begin; it_begin != btree->infix_iterator_end(); ++it_begin) {

			auto btree_sch = reinterpret_cast<Btree<const std::string*, scheme*, string_const_ptr>*>(std::get<1>(*it_begin));
			
			if (!btree_sch->check_tree()) {
				return false;
			}
			
			auto it_begin_scheme = btree_sch->infix_iterator_begin();
			//auto it_end_scheme = btree_sch->infix_iterator_end();

			for (it_begin_scheme; it_begin_scheme != btree_sch->infix_iterator_end(); ++it_begin_scheme) {
			
			
				auto btree_coll = reinterpret_cast<Btree<const std::string*, scheme*, string_const_ptr>*>(std::get<1>(*it_begin_scheme));
				
				if (!btree_coll->check_tree()) {
					return false;
				}

				auto it_begin_collection = btree_coll->infix_iterator_begin();
				//auto it_end_collection = btree_coll->infix_iterator_end();

				for (it_begin_collection; it_begin_collection != btree_coll->infix_iterator_end(); ++it_begin_collection) {

					auto vec_coll = reinterpret_cast<std::vector<collection*>*>(std::get<1>(*it_begin_collection));
					auto btree_data = reinterpret_cast<Btree<contest_info*, contest_info*, comparer_id_member_id_contest>*>((*vec_coll)[0]);

					if (!btree_data->check_tree()) {
						return false;
					}
				}
			}
		}
	}
	else {
		auto btree = (binary_search_tree<const std::string*, pull*, string_const_ptr>*)(d_base->get_dbase());
		auto it_begin = btree->infix_iterator_begin();

		for (it_begin; it_begin != btree->infix_iterator_end(); ++it_begin) {
			
		}
	}
	return true;
}


void dialogue::commands_from_file(std::ifstream& file, data_base* d_base) {
	read_string rstr;
	string_pool* str_p = string_pool::Instance();

	if (!file) {
		file.close();
		throw std::invalid_argument("File is not opened");
	}
	else {
		while (!file.eof()) {
			char input;
			std::string compare;
			rstr.in_str(&compare, &input, file);
			if (compare.compare("create") == 0) {
				compare = "";
				if (rstr.in_str(&compare, &input, file) != 0) {
					file.close();
					throw std::invalid_argument("Wrong input in file");
				}
				if (compare.compare("dbase") == 0) {
					compare = "";
					if (rstr.in_str(&compare, &input, file) == 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					// create dbase
					//data_base::flag::Btree
					if (compare.compare("B-tree") == 0) {
						*d_base = data_base(data_base::flag::Btree, 3);
					}
					else if (compare.compare("AVL") == 0) {

					}
					else if (compare.compare("RB") == 0) {

					}
					else if (compare.compare("Splay") == 0) {

					}
					else {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					continue;
				}
				else if (compare.compare("pull") == 0) {
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					const std::string* name_pull = str_p->get_str(compare);
					compare = "";
					if (rstr.in_str(&compare, &input, file) == 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					// create pull
					if (compare.compare("B-tree") == 0) {
						d_base->create_pull(name_pull, data_base::flag::Btree, 3);
					}
					else if (compare.compare("AVL") == 0) {

					}
					else if (compare.compare("RB") == 0) {

					}
					else if (compare.compare("Splay") == 0) {

					}
					else {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					continue;
				}
				else if (compare.compare("scheme") == 0) {
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					const std::string* pull_name = str_p->get_str(compare);
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					const std::string* scheme_name = str_p->get_str(compare);
					compare = "";
					if (rstr.in_str(&compare, &input, file) == 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					// create scheme
					if (compare.compare("B-tree") == 0) {
						d_base->create_scheme(scheme_name, pull_name, data_base::flag::Btree);
					}
					else if (compare.compare("AVL") == 0) {

					}
					else if (compare.compare("RB") == 0) {

					}
					else if (compare.compare("Splay") == 0) {

					}
					else {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					continue;

				}
				else if (compare.compare("collection") == 0) {
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					const std::string* pull_name = str_p->get_str(compare);
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					const std::string* scheme_name = str_p->get_str(compare);
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					const std::string* name_collection = str_p->get_str(compare);
					compare = "";
					if (rstr.in_str(&compare, &input, file) == 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					if (compare.compare("B-tree") == 0) {
						d_base->create_collection(name_collection, pull_name, scheme_name, data_base::flag::Btree, 3);
					}
					else if (compare.compare("AVL") == 0) {

					}
					else if (compare.compare("RB") == 0) {

					}
					else if (compare.compare("Splay") == 0) {

					}
					else {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					//create collection
					continue;
				}
				else {
					file.close();
					throw std::invalid_argument("Wrong input in file");
				}
				continue;
			}
			else if (compare.compare("delete") == 0) {
				compare = "";
				int temp = rstr.in_str(&compare, &input, file);
				if (compare.compare("dbase") == 0) {
					if (temp == 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					d_base->~data_base();
					//delete dbase
				}
				else if (compare.compare("pull") == 0) {
					if (temp != 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					compare = "";
					int flag_name = rstr.in_str(&compare, &input, file);
					if (flag_name == 0 or flag_name == 3) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					const std::string* pull_name = str_p->get_str(compare);
					// delete pull
					try {
						d_base->delete_pull(pull_name);
					}
					catch (std::invalid_argument& e) {
						throw e;
					}
					continue;
				}
				else if (compare.compare("scheme") == 0) {
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					const std::string* pull_name = str_p->get_str(compare);
					compare = "";
					int flag_name = rstr.in_str(&compare, &input, file);
					if (flag_name == 0 or flag_name == 3) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					const std::string* scheme_name = str_p->get_str(compare);
					try {
						d_base->delete_scheme(scheme_name, pull_name);
					}
					catch (std::invalid_argument& e) {
						throw e;
					}
					continue;

				}
				else if (compare.compare("collection") == 0) {
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					const std::string* pull_name = str_p->get_str(compare);
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					const std::string* scheme_name = str_p->get_str(compare);
					compare = "";
					int flag_name = rstr.in_str(&compare, &input, file);
					if (flag_name == 0 or flag_name == 3) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					const std::string* collection_name = str_p->get_str(compare);
					//delete collection
					try {
						d_base->delete_collection(collection_name, pull_name, scheme_name);
					}
					catch (std::invalid_argument& e) {
						throw e;
					}
					continue;
				}
			}
			else if (compare.compare("collection") == 0) {
				compare = "";
				if (rstr.in_str(&compare, &input, file) != 0) {
					file.close();
					throw std::invalid_argument("Wrong input in file");
				}
				const std::string* name_pull = str_p->get_str(compare);
				compare = "";
				if (rstr.in_str(&compare, &input, file) != 0) {
					file.close();
					throw std::invalid_argument("Wrong input in file");
				}
				const std::string* name_scheme = str_p->get_str(compare);
				compare = "";
				if (rstr.in_str(&compare, &input, file) != 0) {
					file.close();
					throw std::invalid_argument("Wrong input in file");
				}
				const std::string* name_collection = str_p->get_str(compare);
				compare = "";
				if (rstr.in_str(&compare, &input, file) != 0) {
					file.close();
					throw std::invalid_argument("Wrong input in file");
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
					file.close();
					throw std::invalid_argument("Wrong input in file");
				}
				std::vector<collection*> vec_coll;
				collection* collection;
				try {
					vec_coll = d_base->go_to_collection(name_pull, name_scheme, name_collection);
				}
				catch (std::invalid_argument& e) {
					throw e;
				}
				if (flag_tree == 0) {
					collection = vec_coll[0];
				}
				else if (flag_tree == 1) {
					collection = vec_coll[1];
				}
				else {
					file.close();
					throw std::invalid_argument("Wrong input");
				}
				invoker my_invoker;
				std::time_t command_time;
				time_t input_time;
				static std::regex rgx(R"(((([01][0-9])|(2[0-3]))[:]([0-5][0-9])[:]([0-5][0-9]))[-](0[1-9]|[12][0-9]|3[01])\.(0[1-9]|1[012])\.((19|20)\d\d))");
				static std::regex rgx_data(R"((0[1-9]|[12][0-9]|3[01])\.(0[1-9]|1[012])\.((19|20)\d\d))");
				int year, month, day, hour, minute, seconds;
				std::smatch res;
				struct tm tmp = { 0 };
				if (compare.compare("add_node_key") == 0) {
					command_time = time(0) - (3 * 3600);
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					int id_member = std::stoi(compare);
					compare = "";
					if (rstr.in_str_str(&compare, &input, file) != 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					const std::string* name = str_p->get_str(compare);
					compare = "";
					if (rstr.in_str_str(&compare, &input, file) != 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					const std::string* surname = str_p->get_str(compare);
					compare = "";
					if (rstr.in_str_str(&compare, &input, file) != 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					const std::string* patronymic = str_p->get_str(compare);
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					if (std::regex_match(compare, res, rgx_data)) {

						day = std::stoi(res[1].str());
						month = (std::stoi(res[2].str()) - 1);
						year = (std::stoi(res[3].str()) - 1900);

						if (month == 1 and day > 28 and year % 4 != 0 and year != 0) {
							file.close();
							throw std::invalid_argument("Wrong date");
						}
						if (year % 4 == 0 and day != 29) {
							file.close();
							throw std::invalid_argument("Wrong date");
						}
						if (month % 2 == 0 and month != 1 and month != 6 and day == 31) {
							file.close();
							throw std::invalid_argument("Wrong date");
						}
					}
					else {
						file.close();
						throw std::invalid_argument("Wrong input");
					}
					const std::string* day_of_birthday = str_p->get_str(compare);
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					const std::string* resume = str_p->get_str(compare);
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					int id_hrmanager = std::stoi(compare);
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					int id_contest = std::stoi(compare);
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					const std::string* prog_lang = str_p->get_str(compare);
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					int tasks_count = std::stoi(compare);
					compare = "";
					if (rstr.in_str_int(&compare, &input, file) != 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					int tasks_complete = std::stoi(compare);
					compare = "";
					int flag = rstr.in_str_int(&compare, &input, file);
					if (flag == 3 or flag == 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					bool cheating = false;
					if (std::stoi(compare) == 1) {
						cheating = true;
					}
					else if (std::stoi(compare) == 0) {}
					else {
						file.close();
						throw std::invalid_argument("Wrong input in file");
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
						throw e;
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
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						int first_key = std::stoi(compare);
						compare = "";
						if (rstr.in_str_int(&compare, &input, file) != 0) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						int second_key = std::stoi(compare);
						key.set_id_member(first_key);
						key.set_id_contest(second_key);
					}
					else if (flag_tree == 1) {
						compare = "";
						if (rstr.in_str(&compare, &input, file) != 0) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						const std::string* key_resume = str_p->get_str(compare);
						key.set_resume(key_resume);
					}
					else {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					compare = "";
					if (rstr.read_data(&compare, &input, file) == 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
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


						if (month == 1 and day > 28 and year % 4 != 0 and year != 0) {
							file.close();
							throw std::invalid_argument("Wrong date");
						}
						if (year % 4 == 0 and day != 29) {
							file.close();
							throw std::invalid_argument("Wrong date");
						}
						if (month % 2 == 0 and month != 1 and month != 6 and day == 31) {
							file.close();
							throw std::invalid_argument("Wrong date");
						}
						tmp.tm_mday = day;
						tmp.tm_mon = month;
						tmp.tm_year = year;
						input_time = mktime(&tmp);
					}
					else {
						file.close();
						throw std::invalid_argument("Wrong input");
					}
					command* read_node_key_command = new read_node_key(&key, collection, input_time);
					my_invoker.set_command(read_node_key_command);
					try {
						my_invoker.invoke();
					}
					catch (std::invalid_argument& e) {
						throw e;
					}
				}
				else if (compare.compare("read_node_keys") == 0) {
					command_time = time(0);
					contest_info key1;
					contest_info key2;
					if (flag_tree == 0) {
						compare = "";
						if (rstr.in_str_int(&compare, &input, file) != 0) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						int first_first_key = std::stoi(compare);
						compare = "";
						if (rstr.in_str_int(&compare, &input, file) != 0) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						int first_second_key = std::stoi(compare);
						compare = "";
						if (rstr.in_str_int(&compare, &input, file) != 0) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						int second_first_key = std::stoi(compare);
						compare = "";
						if (rstr.in_str_int(&compare, &input, file) != 0) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
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
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						const std::string* key1_resume = str_p->get_str(compare);
						compare = "";
						if (rstr.in_str(&compare, &input, file) != 0) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						const std::string* key2_resume = str_p->get_str(compare);
						key1.set_resume(key1_resume);
						key2.set_resume(key2_resume);
					}
					else {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					compare = "";
					if (rstr.read_data(&compare, &input, file) == 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
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
						if (month == 1 and day > 28 and year % 4 != 0 and year != 0) {
							file.close();
							throw std::invalid_argument("Wrong date");
						}
						if (year % 4 == 0 and day != 29) {
							file.close();
							throw std::invalid_argument("Wrong date");
						}
						if (month % 2 == 0 and month != 1 and month != 6 and day == 31) {
							file.close();
							throw std::invalid_argument("Wrong date");
						}
						tmp.tm_mday = day;
						tmp.tm_mon = month;
						tmp.tm_year = year;
						input_time = mktime(&tmp);
					}
					else {
						file.close();
						throw std::invalid_argument("Wrong input");
					}
					command* read_node_keys_command = new read_node_keys(&key1, &key2, collection, input_time, flag_tree);
					my_invoker.set_command(read_node_keys_command);
					try {
						my_invoker.invoke();
					}
					catch (std::invalid_argument& e) {
						throw e;
					}
				}
				else if (compare.compare("update_node_key") == 0) {
					command_time = time(0) - (3 * 3600);
					//first key
					contest_info key;
					if (flag_tree == 0) {
						compare = "";
						if (rstr.in_str_int(&compare, &input, file) != 0) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						int first_key = std::stoi(compare);
						compare = "";
						if (rstr.in_str_int(&compare, &input, file) != 0) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						int second_key = std::stoi(compare);
						key.set_id_member(first_key);
						key.set_id_contest(second_key);
					}
					else if (flag_tree == 1) {
						compare = "";
						if (rstr.in_str(&compare, &input, file) != 0) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						const std::string* key_resume = str_p->get_str(compare);
						key.set_resume(key_resume);
					}
					else {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					compare = "";
					if (rstr.in_str(&compare, &input, file) != 0) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					const std::string* flag = str_p->get_str(compare);
					compare = "";
					command* update_node_key_command;
					if (*flag == "id_member") {
						int flag_value = rstr.in_str_int(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						int value = std::stoi(compare);
						update_node_key_command = new update_node_key_id_member(value, command_time);
					}
					else if (*flag == "name") {
						int flag_value = rstr.in_str(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						const std::string* value = str_p->get_str(compare);
						update_node_key_command = new update_node_key_name(value, command_time);
					}
					else if (*flag == "surname") {
						int flag_value = rstr.in_str(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						const std::string* value = str_p->get_str(compare);
						update_node_key_command = new update_node_key_surname(value, command_time);
					}
					else if (*flag == "patronymic") {
						int flag_value = rstr.in_str(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						const std::string* value = str_p->get_str(compare);
						update_node_key_command = new update_node_key_patronymic(value, command_time);
					}
					else if (*flag == "day_of_birthday") {
						int flag_value = rstr.in_str(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						if (std::regex_match(compare, res, rgx_data)) {
							day = std::stoi(res[2].str());
							month = (std::stoi(res[3].str()) - 1);
							year = (std::stoi(res[4].str()) - 1900);
							if (month == 1 and day > 28 and year % 4 != 0 and year != 0) {
								file.close();
								throw std::invalid_argument("Wrong date");
							}
							if (year % 4 == 0 and day != 29) {
								file.close();
								throw std::invalid_argument("Wrong date");
							}
							if (month % 2 == 0 and month != 1 and month != 6 and day == 31) {
								file.close();
								throw std::invalid_argument("Wrong date");
							}
						}
						else {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						const std::string* value = str_p->get_str(compare);
						update_node_key_command = new update_node_key_day_of_birthday(value, command_time);
					}
					else if (*flag == "resume") {
						int flag_value = rstr.in_str(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						const std::string* value = str_p->get_str(compare);
						update_node_key_command = new update_node_key_resume(value, command_time);
					}
					else if (*flag == "id_hrmanager") {
						int flag_value = rstr.in_str_int(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						int value = std::stoi(compare);
						update_node_key_command = new update_node_key_id_hrmanager(value, command_time);
					}
					else if (*flag == "id_contest") {
						int flag_value = rstr.in_str_int(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						int value = std::stoi(compare);
						update_node_key_command = new update_node_key_id_contest(value, command_time);
					}
					else if (*flag == "prog_lang") {
						int flag_value = rstr.in_str(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						const std::string* value = str_p->get_str(compare);
						update_node_key_command = new update_node_key_prog_lang(value, command_time);
					}
					else if (*flag == "tasks_count") {
						int flag_value = rstr.in_str_int(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						int value = std::stoi(compare);
						update_node_key_command = new update_node_key_tasks_count(value, command_time);
					}
					else if (*flag == "tasks_complete") {
						int flag_value = rstr.in_str_int(&compare, &input, file);
						if (flag_value == 3 or flag_value == 0) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						int value = std::stoi(compare);
						update_node_key_command = new update_node_key_tasks_complete(value, command_time);
					}
					else if (*flag == "cheating") {
						int flag_cheat = rstr.in_str_int(&compare, &input, file);
						if (flag_cheat == 0 or flag_cheat == 3) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						bool value = false;
						if (std::stoi(compare) == 1) {
							value = true;
						}
						else if (std::stoi(compare) == 0) {}
						else {
							file.close();
							throw std::invalid_argument("Wrong input in file");
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
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					contest_info* right_member;
					try {
						right_member = d_base->go_to_contest_info(collection, &key);
					}
					catch (std::invalid_argument& e) {
						file.close();
						throw std::invalid_argument("Wrong input in file");
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
									try {
										my_invoker.add_command(*std::get<1>(*it), update_node_key_command);
									}
									catch (std::invalid_argument& e) {
										throw e;
									}
									break;
								}
							}
						}
						else if (dynamic_cast<binary_search_tree<contest_info*, contest_info*, comparer_id_member_id_contest>*>((collection_default*)vec_coll[flag_tree])) {
							binary_search_tree<contest_info*, contest_info*, comparer_id_member_id_contest>* _btree =
								dynamic_cast<binary_search_tree<contest_info*, contest_info*, comparer_id_member_id_contest>*>((collection_default*)vec_coll[flag_tree]);
							command* temp;
							contest_info copy_value;
							auto it = _btree->infix_iterator_begin();
							for (it; it != _btree->infix_iterator_end(); ++it) {
								if (_comp.comparate(std::get<0>(*it), &key) == 0) {
									try {
										my_invoker.add_command(*std::get<1>(*it), update_node_key_command);
									}
									catch (std::invalid_argument& e) {
										throw e;
									}
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
										throw e;
									}
									break;
								}
							}
						}
						else if (dynamic_cast<binary_search_tree<contest_info*, contest_info*, comparer_id_member_id_contest>*>((collection_default*)vec_coll[flag_tree])) {
							binary_search_tree<contest_info*, contest_info*, comparer_id_member_id_contest>* _btree =
								dynamic_cast<binary_search_tree<contest_info*, contest_info*, comparer_id_member_id_contest>*>((collection_default*)vec_coll[flag_tree]);
							command* temp;
							contest_info copy_value;
							auto it = _btree->infix_iterator_begin();
							for (it; it != _btree->infix_iterator_end(); ++it) {
								if (_comp_resume.comparate(std::get<0>(*it), &key) == 0) {
									try {
										my_invoker.add_command(*std::get<1>(*it), update_node_key_command);
									}
									catch (std::invalid_argument& e) {
										throw e;
									}
									break;
								}
							}
						}
					}
					else {
						file.close();
						throw std::invalid_argument("Wrong tree");
					}
				}
				else if (compare.compare("remove_node_key") == 0) {
					command_time = time(0) - (3 * 3600);
					//first key
					contest_info key;
					if (flag_tree == 0) {
						compare = "";
						if (rstr.in_str_int(&compare, &input, file) != 0) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						int first_key = std::stoi(compare);
						compare = "";
						int flag_remove = rstr.in_str_int(&compare, &input, file);
						if (flag_remove == 0 or flag_remove == 3) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						int second_key = std::stoi(compare);
						key.set_id_member(first_key);
						key.set_id_contest(second_key);
					}
					else if (flag_tree == 1) {
						compare = "";
						int flag_remove = rstr.in_str(&compare, &input, file);

						if (flag_remove == 0 or flag_remove == 3) {
							file.close();
							throw std::invalid_argument("Wrong input in file");
						}
						const std::string* key_resume = str_p->get_str(compare);
						key.set_resume(key_resume);
					}
					else {
						file.close();
						throw std::invalid_argument("Wrong input in file");
					}
					// get contest_info from collection
					contest_info* member;

					command* remove_node_key_command = new remove_node_key(&key, vec_coll[flag_tree], command_time);
					try {
						member = d_base->go_to_contest_info(vec_coll[flag_tree], &key);
					}
					catch (std::invalid_argument& e) {
						file.close();
						throw e;
					}
					try {
						my_invoker.add_command(*member, remove_node_key_command);
					}
					catch (std::invalid_argument& e) {
						throw e;
					}
					try {
						member = d_base->go_to_contest_info(collection, &key);
					}
					catch (std::invalid_argument& e) {
						file.close();
						throw e;
					}

				}
				else {
					file.close();
					throw std::invalid_argument("Wrong input in file");
				}
			}
			/*else if (compare == "save") {
				compare = "";
				int flag_save = rstr.in_str(&compare, &input, file);
				if (flag_save == 0 or flag_save == 3) {
					file.close();
					throw std::invalid_argument("Wrong input in file");
				}
				dbase_safe saver(compare, d_base, data_base::flag::Btree);
				saver.save();
			}
			else if (compare == "upload") {
				compare = "";
				int flag_save = rstr.in_str(&compare, &input, file);
				if (flag_save == 0 or flag_save == 3) {
					file.close();
					throw std::invalid_argument("Wrong input in file");
				}
				data_base d_base = data_base(data_base::flag::Btree, 3);
				dbase_safe saver(compare, &d_base, data_base::flag::Btree);
				saver.restore();
			}*/
			else {
				file.close();
				throw std::invalid_argument("Wrong input in file");
			}
		}
	}
	file.close();
}