#ifndef DBASE_SAFE
#define DBASE_SAFE

#include <vector>
#include <stdexcept>
#include <string>
#include <fstream>
#include <type_traits>
#include <vector>

#include "DataBase.h"
#include "stringpool.h"
#include "contest_info.h"
#include "commands.h"


class dbase_safe {

private:

	std::string _path;

	data_base* _dbase;

	data_base::flag _type_tree;

public:

	dbase_safe(std::string path, data_base* dbase, data_base::flag type_tree) :
		_path(path), _dbase(dbase), _type_tree(type_tree) {}

	dbase_safe() = default;

	dbase_safe(dbase_safe&& other) {
		_path = other._path;

		_dbase = other._dbase;
		delete other._dbase;

		_type_tree = other._type_tree;
	}

	bool operator==(const dbase_safe& other) {
		if (this->_dbase == other._dbase and this->_path == other._path and this->_type_tree == other._type_tree) {
			return true;
		}
		else {
			return false;
		}
	}

	dbase_safe& operator=(dbase_safe&& other) {
		if (!(*this == other)) {
			_path = other._path;

			_dbase = other._dbase;

			_type_tree = other._type_tree;
		}
		return *this;
	}

	~dbase_safe() = default;

public:

	void save() {
		std::ofstream fout;
		fout.open(_path, std::ios::binary);
		if (!fout.is_open()) {
			throw std::invalid_argument("Problems with file path");
		}

		if (_type_tree == data_base::flag::Btree) {
			std::string tree_type = "Btree";
			unsigned int tree_type_size = tree_type.size();
			fout.write(reinterpret_cast<char*>(&tree_type_size), sizeof(unsigned int));
			fout.write(tree_type.c_str(), sizeof(char) * tree_type_size);
		}
		else if (_type_tree == data_base::flag::AVL) {
			std::string tree_type = "AVL";
			unsigned int tree_type_size = tree_type.size();
			fout.write(reinterpret_cast<char*>(&tree_type_size), sizeof(unsigned int));
			fout.write(tree_type.c_str(), sizeof(char) * tree_type_size);
		}
		else if (_type_tree == data_base::flag::Splay) {
			std::string tree_type = "Splay";
			unsigned int tree_type_size = tree_type.size();
			fout.write(reinterpret_cast<char*>(&tree_type_size), sizeof(unsigned int));
			fout.write(tree_type.c_str(), sizeof(char) * tree_type_size);
		}
		else {
			throw std::invalid_argument("Wrong type tree");
		}

		if (dynamic_cast<Btree<const std::string*, pull*, string_const_ptr>*>(_dbase->get_dbase())) {
			//reinterpret_cast<Btree<std::string, pull*, string_comparer>*>
			auto btree = (Btree<const std::string*, pull*, string_const_ptr>*)(_dbase->get_dbase());
			auto it_begin = btree->infix_iterator_begin();
			//auto it_end = btree->infix_iterator_end();

			for (it_begin; it_begin != btree->infix_iterator_end(); ++it_begin) {
				fout.write("#", sizeof(char));

				std::string pool_name = *std::get<0>(*it_begin);
				unsigned int pool_name_size = pool_name.size();
				fout.write(reinterpret_cast<char*>(&pool_name_size), sizeof(unsigned int));
				fout.write(pool_name.c_str(), sizeof(char) * pool_name_size);

				auto btree_sch = reinterpret_cast<Btree<const std::string*, scheme*, string_const_ptr>*>(std::get<1>(*it_begin));
				auto it_begin_scheme = btree_sch->infix_iterator_begin();
				//auto it_end_scheme = btree_sch->infix_iterator_end();

				for (it_begin_scheme; it_begin_scheme != btree_sch->infix_iterator_end(); ++it_begin_scheme) {

					fout.write("^", sizeof(char));

					std::string scheme_name = *std::get<0>(*it_begin_scheme);
					unsigned int scheme_name_size = (scheme_name).size();
					fout.write(reinterpret_cast<char*>(&scheme_name_size), sizeof(unsigned int));
					fout.write(scheme_name.c_str(), sizeof(char) * scheme_name_size);

					/*auto vec_coll = reinterpret_cast<std::vector<collection*>*>(std::get<1>(*it_begin_scheme));
					auto btree_coll = reinterpret_cast<Btree<contest_info*, contest_info*, comparer_id_member_id_contest>*>((*vec_coll)[0]);*/
					auto btree_coll = reinterpret_cast<Btree<const std::string*, scheme*, string_const_ptr>*>(std::get<1>(*it_begin_scheme));
					auto it_begin_collection = btree_coll->infix_iterator_begin();
					//auto it_end_collection = btree_coll->infix_iterator_end();

					for (it_begin_collection; it_begin_collection != btree_coll->infix_iterator_end(); ++it_begin_collection) {

						fout.write("&", sizeof(char));

						std::string coll_name = *std::get<0>(*it_begin_collection);
						unsigned int coll_name_size = (coll_name).size();
						fout.write(reinterpret_cast<char*>(&coll_name_size), sizeof(unsigned int));
						fout.write(coll_name.c_str(), sizeof(char) * coll_name_size);

						auto vec_coll = reinterpret_cast<std::vector<collection*>*>(std::get<1>(*it_begin_collection));
						auto btree_data = reinterpret_cast<Btree<contest_info*, contest_info*, comparer_id_member_id_contest>*>((*vec_coll)[0]);
						//auto btree_data = reinterpret_cast<Btree<contest_info*, contest_info*, comparer_id_member_id_contest>*>
							//(std::get<1>(*it_begin_collection));
						auto it_begin_data = btree_data->infix_iterator_begin();
						//auto it_end_data = btree_data->infix_iterator_end();

						for (it_begin_data; it_begin_data != btree_data->infix_iterator_end(); ++it_begin_data) {

							fout.write("!", sizeof(char));
							auto temp_contest = (std::get<1>(*it_begin_data));

							command* first_command = temp_contest->first_command;

							while (first_command != nullptr) {

								fout.write("@", sizeof(char));

								unsigned long long time = first_command->_time;
								fout.write(reinterpret_cast<char*>(&time), sizeof(unsigned long long));

								if (dynamic_cast<add_node_key*>(first_command)) {
									std::string* com = new std::string("add_node_key");
									add_node_key* command = dynamic_cast<add_node_key*>(first_command);
									contest_info _key = command->get_value();
									int id_member = _key.get_id_member();
									const std::string* name = _key.get_name();
									const std::string* surname = _key.get_surname();
									const std::string* patronymic = _key.get_patronymic();
									const std::string* day_of_birthday = _key.get_day_of_birthday();
									const std::string* resume = _key.get_resume();
									const std::string* prog_lang = _key.get_prog_lang();
									int id_hrmanager = _key.get_id_hrmanager();
									int id_contest = _key.get_id_contest();
									int tasks_count = _key.get_tasks_count();
									int tasks_complete = _key.get_tasks_complete();
									std::string cheating = ((_key.get_cheating()) ? "true" : "false");

									unsigned int com_size = com->size();
									fout.write(reinterpret_cast<char*>(&com_size), sizeof(unsigned int));
									fout.write(com->c_str(), sizeof(char) * com_size);

									fout.write(reinterpret_cast<char*>(&id_member), sizeof(int));

									unsigned int name_size = name->size();
									fout.write(reinterpret_cast<char*>(&name_size), sizeof(unsigned int));
									fout.write(name->c_str(), sizeof(char) * name_size);

									unsigned int surname_size = surname->size();
									fout.write(reinterpret_cast<char*>(&surname_size), sizeof(unsigned int));
									fout.write(surname->c_str(), sizeof(char) * surname_size);

									unsigned int patronymic_size = patronymic->size();
									fout.write(reinterpret_cast<char*>(&patronymic_size), sizeof(unsigned int));
									fout.write(patronymic->c_str(), sizeof(char) * patronymic_size);

									unsigned int day_of_birthday_size = day_of_birthday->size();
									fout.write(reinterpret_cast<char*>(&day_of_birthday_size), sizeof(unsigned int));
									fout.write(day_of_birthday->c_str(), sizeof(char) * day_of_birthday_size);

									unsigned int resume_size = resume->size();
									fout.write(reinterpret_cast<char*>(&resume_size), sizeof(unsigned int));
									fout.write(resume->c_str(), sizeof(char) * resume_size);

									fout.write(reinterpret_cast<char*>(&id_hrmanager), sizeof(int));

									fout.write(reinterpret_cast<char*>(&id_contest), sizeof(int));

									unsigned int prog_lang_size = prog_lang->size();
									fout.write(reinterpret_cast<char*>(&prog_lang_size), sizeof(unsigned int));
									fout.write(prog_lang->c_str(), sizeof(char) * prog_lang_size);

									fout.write(reinterpret_cast<char*>(&tasks_count), sizeof(int));

									fout.write(reinterpret_cast<char*>(&tasks_complete), sizeof(int));

									unsigned int cheating_size = cheating.size();
									fout.write(reinterpret_cast<char*>(&cheating_size), sizeof(unsigned int));
									fout.write(cheating.c_str(), sizeof(char) * cheating_size);

									delete com;
								}
								else if (dynamic_cast<update_node_key_name*>(first_command)) {
									std::string* com = new std::string("update_node_key_name");
									update_node_key_name* command = dynamic_cast<update_node_key_name*>(first_command);
									std::string _key = command->get_value();

									unsigned int com_size = com->size();
									fout.write(reinterpret_cast<char*>(&com_size), sizeof(unsigned int));
									fout.write(com->c_str(), sizeof(char) * com_size);

									unsigned int _key_size = _key.size();
									fout.write(reinterpret_cast<char*>(&_key_size), sizeof(unsigned int));
									fout.write(_key.c_str(), sizeof(char) * _key_size);
								}
								else if (dynamic_cast<update_node_key_surname*>(first_command)) {
									std::string* com = new std::string("update_node_key_surname");
									update_node_key_surname* command = dynamic_cast<update_node_key_surname*>(first_command);
									std::string _key = command->get_value();

									unsigned int com_size = com->size();
									fout.write(reinterpret_cast<char*>(&com_size), sizeof(unsigned int));
									fout.write(com->c_str(), sizeof(char) * com_size);

									unsigned int _key_size = _key.size();
									fout.write(reinterpret_cast<char*>(&_key_size), sizeof(unsigned int));
									fout.write(_key.c_str(), sizeof(char) * _key_size);
								}
								else if (dynamic_cast<update_node_key_patronymic*>(first_command)) {
									std::string* com = new std::string("update_node_key_patronymic");
									update_node_key_patronymic* command = dynamic_cast<update_node_key_patronymic*>(first_command);
									std::string _key = command->get_value();

									unsigned int com_size = com->size();
									fout.write(reinterpret_cast<char*>(&com_size), sizeof(unsigned int));
									fout.write(com->c_str(), sizeof(char) * com_size);

									unsigned int _key_size = _key.size();
									fout.write(reinterpret_cast<char*>(&_key_size), sizeof(unsigned int));
									fout.write(_key.c_str(), sizeof(char) * _key_size);
								}
								else if (dynamic_cast<update_node_key_day_of_birthday*>(first_command)) {
									std::string* com = new std::string("update_node_key_day_of_birthday");
									update_node_key_day_of_birthday* command = dynamic_cast<update_node_key_day_of_birthday*>(first_command);
									std::string _key = command->get_value();

									unsigned int com_size = com->size();
									fout.write(reinterpret_cast<char*>(&com_size), sizeof(unsigned int));
									fout.write(com->c_str(), sizeof(char) * com_size);

									unsigned int _key_size = _key.size();
									fout.write(reinterpret_cast<char*>(&_key_size), sizeof(unsigned int));
									fout.write(_key.c_str(), sizeof(char) * _key_size);
								}
								else if (dynamic_cast<update_node_key_id_hrmanager*>(first_command)) {
									std::string* com = new std::string("update_node_key_id_hrmanager");
									update_node_key_id_hrmanager* command = dynamic_cast<update_node_key_id_hrmanager*>(first_command);
									int _key = command->get_value();

									unsigned int com_size = com->size();
									fout.write(reinterpret_cast<char*>(&com_size), sizeof(unsigned int));
									fout.write(com->c_str(), sizeof(char) * com_size);

									fout.write(reinterpret_cast<char*>(&_key), sizeof(int));
								}
								else if (dynamic_cast<update_node_key_tasks_count*>(first_command)) {
									std::string* com = new std::string("update_node_key_tasks_count");
									update_node_key_tasks_count* command = dynamic_cast<update_node_key_tasks_count*>(first_command);
									int _key = command->get_value();

									unsigned int com_size = com->size();
									fout.write(reinterpret_cast<char*>(&com_size), sizeof(unsigned int));
									fout.write(com->c_str(), sizeof(char) * com_size);

									fout.write(reinterpret_cast<char*>(&_key), sizeof(int));
								}
								else if (dynamic_cast<update_node_key_tasks_complete*>(first_command)) {
									std::string* com = new std::string("update_node_key_tasks_complete");
									update_node_key_tasks_complete* command = dynamic_cast<update_node_key_tasks_complete*>(first_command);
									int _key = command->get_value();

									unsigned int com_size = com->size();
									fout.write(reinterpret_cast<char*>(&com_size), sizeof(unsigned int));
									fout.write(com->c_str(), sizeof(char) * com_size);

									fout.write(reinterpret_cast<char*>(&_key), sizeof(int));
								}
								else if (dynamic_cast<update_node_key_cheating*>(first_command)) {
									std::string* com = new std::string("update_node_key_cheating");
									update_node_key_cheating* command = dynamic_cast<update_node_key_cheating*>(first_command);
									bool _key = command->get_value();

									unsigned int com_size = com->size();
									fout.write(reinterpret_cast<char*>(&com_size), sizeof(unsigned int));
									fout.write(com->c_str(), sizeof(char) * com_size);

									fout.write(reinterpret_cast<char*>(&_key), sizeof(bool));
								}
								else if (dynamic_cast<remove_node_key*>(first_command)) {
									std::string* com = new std::string("remove_node_key");
									remove_node_key* command = dynamic_cast<remove_node_key*>(first_command);
									contest_info _key = command->get_value();

									unsigned int com_size = com->size();
									fout.write(reinterpret_cast<char*>(&com_size), sizeof(unsigned int));
									fout.write(com->c_str(), sizeof(char) * com_size);

									int key_idmember = _key.get_id_member();
									int key_contest = _key.get_id_contest();

									fout.write(reinterpret_cast<char*>(&key_idmember), sizeof(int));
									fout.write(reinterpret_cast<char*>(&key_contest), sizeof(int));
								}
								first_command = first_command->next_command;
							}

						}
					}
				}
			}
			fout.write("%", sizeof(char));
			//saving the tree
		}
		else {
			//doing iterator from binary_search_tree

			auto btree = (binary_search_tree<const std::string*, pull*, string_const_ptr>*)(_dbase->get_dbase());
			auto it_begin = btree->infix_iterator_begin();

			//auto it_end = btree->infix_iterator_end();
			for (it_begin; it_begin != btree->infix_iterator_end(); ++it_begin) {
				fout.write("#", sizeof(char));
				std::string pool_name = *std::get<0>(*it_begin);
				unsigned int pool_name_size = pool_name.size();
				fout.write(reinterpret_cast<char*>(&pool_name_size), sizeof(unsigned int));
				fout.write(pool_name.c_str(), sizeof(char) * pool_name_size);

				auto btree_sch = reinterpret_cast<Btree<const std::string*, scheme*, string_const_ptr>*>(std::get<1>(*it_begin));
				auto it_begin_scheme = btree_sch->infix_iterator_begin();
				//auto it_end_scheme = btree_sch->infix_iterator_end();

				for (it_begin_scheme; it_begin_scheme != btree_sch->infix_iterator_end(); ++it_begin_scheme) {

					fout.write("^", sizeof(char));

					std::string scheme_name = *std::get<0>(*it_begin_scheme);
					unsigned int scheme_name_size = (scheme_name).size();
					fout.write(reinterpret_cast<char*>(&scheme_name_size), sizeof(unsigned int));
					fout.write(scheme_name.c_str(), sizeof(char) * scheme_name_size);

					/*auto vec_coll = reinterpret_cast<std::vector<collection*>*>(std::get<1>(*it_begin_scheme));
					auto btree_coll = reinterpret_cast<Btree<contest_info*, contest_info*, comparer_id_member_id_contest>*>((*vec_coll)[0]);*/
					auto btree_coll = reinterpret_cast<Btree<const std::string*, scheme*, string_const_ptr>*>(std::get<1>(*it_begin_scheme));
					auto it_begin_collection = btree_coll->infix_iterator_begin();
					//auto it_end_collection = btree_coll->infix_iterator_end();

					for (it_begin_collection; it_begin_collection != btree_coll->infix_iterator_end(); ++it_begin_collection) {

						fout.write("&", sizeof(char));

						std::string coll_name = *std::get<0>(*it_begin_collection);
						unsigned int coll_name_size = (coll_name).size();
						fout.write(reinterpret_cast<char*>(&coll_name_size), sizeof(unsigned int));
						fout.write(coll_name.c_str(), sizeof(char) * coll_name_size);

						auto vec_coll = reinterpret_cast<std::vector<collection*>*>(std::get<1>(*it_begin_collection));
						auto btree_data = reinterpret_cast<Btree<contest_info*, contest_info*, comparer_id_member_id_contest>*>((*vec_coll)[0]);
						//auto btree_data = reinterpret_cast<Btree<contest_info*, contest_info*, comparer_id_member_id_contest>*>
							//(std::get<1>(*it_begin_collection));
						auto it_begin_data = btree_data->infix_iterator_begin();
						//auto it_end_data = btree_data->infix_iterator_end();

						for (it_begin_data; it_begin_data != btree_data->infix_iterator_end(); ++it_begin_data) {

							fout.write("!", sizeof(char));
							auto temp_contest = (std::get<1>(*it_begin_data));

							command* first_command = temp_contest->first_command;

							while (first_command != nullptr) {

								fout.write("@", sizeof(char));

								unsigned long long time = first_command->_time;
								fout.write(reinterpret_cast<char*>(&time), sizeof(unsigned long long));

								if (dynamic_cast<add_node_key*>(first_command)) {
									std::string* com = new std::string("add_node_key");
									add_node_key* command = dynamic_cast<add_node_key*>(first_command);
									contest_info _key = command->get_value();
									int id_member = _key.get_id_member();
									const std::string* name = _key.get_name();
									const std::string* surname = _key.get_surname();
									const std::string* patronymic = _key.get_patronymic();
									const std::string* day_of_birthday = _key.get_day_of_birthday();
									const std::string* resume = _key.get_resume();
									const std::string* prog_lang = _key.get_prog_lang();
									int id_hrmanager = _key.get_id_hrmanager();
									int id_contest = _key.get_id_contest();
									int tasks_count = _key.get_tasks_count();
									int tasks_complete = _key.get_tasks_complete();
									std::string cheating = ((_key.get_cheating()) ? "true" : "false");

									unsigned int com_size = com->size();
									fout.write(reinterpret_cast<char*>(&com_size), sizeof(unsigned int));
									fout.write(com->c_str(), sizeof(char) * com_size);

									fout.write(reinterpret_cast<char*>(&id_member), sizeof(int));

									unsigned int name_size = name->size();
									fout.write(reinterpret_cast<char*>(&name_size), sizeof(unsigned int));
									fout.write(name->c_str(), sizeof(char) * name_size);

									unsigned int surname_size = surname->size();
									fout.write(reinterpret_cast<char*>(&surname_size), sizeof(unsigned int));
									fout.write(surname->c_str(), sizeof(char) * surname_size);

									unsigned int patronymic_size = patronymic->size();
									fout.write(reinterpret_cast<char*>(&patronymic_size), sizeof(unsigned int));
									fout.write(patronymic->c_str(), sizeof(char) * patronymic_size);

									unsigned int day_of_birthday_size = day_of_birthday->size();
									fout.write(reinterpret_cast<char*>(&day_of_birthday_size), sizeof(unsigned int));
									fout.write(day_of_birthday->c_str(), sizeof(char) * day_of_birthday_size);

									unsigned int resume_size = resume->size();
									fout.write(reinterpret_cast<char*>(&resume_size), sizeof(unsigned int));
									fout.write(resume->c_str(), sizeof(char) * resume_size);

									fout.write(reinterpret_cast<char*>(&id_hrmanager), sizeof(int));

									fout.write(reinterpret_cast<char*>(&id_contest), sizeof(int));

									unsigned int prog_lang_size = prog_lang->size();
									fout.write(reinterpret_cast<char*>(&prog_lang_size), sizeof(unsigned int));
									fout.write(prog_lang->c_str(), sizeof(char) * prog_lang_size);

									fout.write(reinterpret_cast<char*>(&tasks_count), sizeof(int));

									fout.write(reinterpret_cast<char*>(&tasks_complete), sizeof(int));

									unsigned int cheating_size = cheating.size();
									fout.write(reinterpret_cast<char*>(&cheating_size), sizeof(unsigned int));
									fout.write(cheating.c_str(), sizeof(char) * cheating_size);

									delete com;
								}
								else if (dynamic_cast<update_node_key_name*>(first_command)) {
									std::string* com = new std::string("update_node_key_name");
									update_node_key_name* command = dynamic_cast<update_node_key_name*>(first_command);
									std::string _key = command->get_value();

									unsigned int com_size = com->size();
									fout.write(reinterpret_cast<char*>(&com_size), sizeof(unsigned int));
									fout.write(com->c_str(), sizeof(char) * com_size);

									unsigned int _key_size = _key.size();
									fout.write(reinterpret_cast<char*>(&_key_size), sizeof(unsigned int));
									fout.write(_key.c_str(), sizeof(char) * _key_size);
								}
								else if (dynamic_cast<update_node_key_surname*>(first_command)) {
									std::string* com = new std::string("update_node_key_surname");
									update_node_key_surname* command = dynamic_cast<update_node_key_surname*>(first_command);
									std::string _key = command->get_value();

									unsigned int com_size = com->size();
									fout.write(reinterpret_cast<char*>(&com_size), sizeof(unsigned int));
									fout.write(com->c_str(), sizeof(char) * com_size);

									unsigned int _key_size = _key.size();
									fout.write(reinterpret_cast<char*>(&_key_size), sizeof(unsigned int));
									fout.write(_key.c_str(), sizeof(char) * _key_size);
								}
								else if (dynamic_cast<update_node_key_patronymic*>(first_command)) {
									std::string* com = new std::string("update_node_key_patronymic");
									update_node_key_patronymic* command = dynamic_cast<update_node_key_patronymic*>(first_command);
									std::string _key = command->get_value();

									unsigned int com_size = com->size();
									fout.write(reinterpret_cast<char*>(&com_size), sizeof(unsigned int));
									fout.write(com->c_str(), sizeof(char) * com_size);

									unsigned int _key_size = _key.size();
									fout.write(reinterpret_cast<char*>(&_key_size), sizeof(unsigned int));
									fout.write(_key.c_str(), sizeof(char) * _key_size);
								}
								else if (dynamic_cast<update_node_key_day_of_birthday*>(first_command)) {
									std::string* com = new std::string("update_node_key_day_of_birthday");
									update_node_key_day_of_birthday* command = dynamic_cast<update_node_key_day_of_birthday*>(first_command);
									std::string _key = command->get_value();

									unsigned int com_size = com->size();
									fout.write(reinterpret_cast<char*>(&com_size), sizeof(unsigned int));
									fout.write(com->c_str(), sizeof(char) * com_size);

									unsigned int _key_size = _key.size();
									fout.write(reinterpret_cast<char*>(&_key_size), sizeof(unsigned int));
									fout.write(_key.c_str(), sizeof(char) * _key_size);
								}
								else if (dynamic_cast<update_node_key_id_hrmanager*>(first_command)) {
									std::string* com = new std::string("update_node_key_id_hrmanager");
									update_node_key_id_hrmanager* command = dynamic_cast<update_node_key_id_hrmanager*>(first_command);
									int _key = command->get_value();

									unsigned int com_size = com->size();
									fout.write(reinterpret_cast<char*>(&com_size), sizeof(unsigned int));
									fout.write(com->c_str(), sizeof(char) * com_size);

									fout.write(reinterpret_cast<char*>(&_key), sizeof(int));
								}
								else if (dynamic_cast<update_node_key_tasks_count*>(first_command)) {
									std::string* com = new std::string("update_node_key_tasks_count");
									update_node_key_tasks_count* command = dynamic_cast<update_node_key_tasks_count*>(first_command);
									int _key = command->get_value();

									unsigned int com_size = com->size();
									fout.write(reinterpret_cast<char*>(&com_size), sizeof(unsigned int));
									fout.write(com->c_str(), sizeof(char) * com_size);

									fout.write(reinterpret_cast<char*>(&_key), sizeof(int));
								}
								else if (dynamic_cast<update_node_key_tasks_complete*>(first_command)) {
									std::string* com = new std::string("update_node_key_tasks_complete");
									update_node_key_tasks_complete* command = dynamic_cast<update_node_key_tasks_complete*>(first_command);
									int _key = command->get_value();

									unsigned int com_size = com->size();
									fout.write(reinterpret_cast<char*>(&com_size), sizeof(unsigned int));
									fout.write(com->c_str(), sizeof(char) * com_size);

									fout.write(reinterpret_cast<char*>(&_key), sizeof(int));
								}
								else if (dynamic_cast<update_node_key_cheating*>(first_command)) {
									std::string* com = new std::string("update_node_key_cheating");
									update_node_key_cheating* command = dynamic_cast<update_node_key_cheating*>(first_command);
									bool _key = command->get_value();

									unsigned int com_size = com->size();
									fout.write(reinterpret_cast<char*>(&com_size), sizeof(unsigned int));
									fout.write(com->c_str(), sizeof(char) * com_size);

									fout.write(reinterpret_cast<char*>(&_key), sizeof(bool));
								}
								else if (dynamic_cast<remove_node_key*>(first_command)) {
									std::string* com = new std::string("remove_node_key");
									remove_node_key* command = dynamic_cast<remove_node_key*>(first_command);
									contest_info _key = command->get_value();

									unsigned int com_size = com->size();
									fout.write(reinterpret_cast<char*>(&com_size), sizeof(unsigned int));
									fout.write(com->c_str(), sizeof(char) * com_size);

									int key_idmember = _key.get_id_member();
									int key_contest = _key.get_id_contest();

									fout.write(reinterpret_cast<char*>(&key_idmember), sizeof(int));
									fout.write(reinterpret_cast<char*>(&key_contest), sizeof(int));
								}
								first_command = first_command->next_command;
							}

						}
					}
				}
			}
			fout.write("%", sizeof(char));
		}

		fout.close();
	}

	void read_string_from_binary_file(std::ifstream& in, char** string_buffer) {
		static unsigned int buffer_length = 100;

		unsigned int string_length;

		in.read(reinterpret_cast<char*>(&string_length), sizeof(unsigned int));

		while (buffer_length + 1 < string_length) {
			char* possible_buffer = (char*)realloc(*string_buffer, sizeof(char) * buffer_length * 2);
			if (possible_buffer == NULL) {
				free(*string_buffer);
				throw std::runtime_error("Memory allocate exception! Cannot reallocate memory while restoring tree. ");
			}
			buffer_length *= 2;
			*string_buffer = possible_buffer;
		}

		in.read(*string_buffer, sizeof(char) * string_length);

		(*string_buffer)[string_length] = '\0';
	}

	data_base* restore(data_base::flag& flag_tree) {
		std::ifstream fin(_path, std::ios::binary);
		if (!fin.is_open()) {
			throw std::invalid_argument("File is not exist");
		}

		char char_token;
		long long_taken;
		char* string_buffer;
		std::vector<const std::string*> path(3);
		string_pool* _str_p = string_pool::Instance();
		if ((string_buffer = (char*)malloc(sizeof(char) * 100)) == NULL) {
			throw std::runtime_error("Memory allocate exception! Cannot allocate memory while restoring tree.");
		}

		read_string_from_binary_file(fin, &string_buffer);

		std::string type_tree = string_buffer;

		if (type_tree == "Btree") {
			_dbase = new data_base(data_base::flag::Btree, 3);
			flag_tree = data_base::flag::Btree;
		}
		else if (type_tree == "AVL") {
			_dbase = new data_base(data_base::flag::AVL);
			flag_tree = data_base::flag::AVL;
		}
		else if (type_tree == "Splay") {
			_dbase = new data_base(data_base::flag::Splay);
			flag_tree = data_base::flag::Splay;
		}
		else {
			throw std::invalid_argument("Wrong type tree");
		}

		fin.read(&char_token, sizeof(char));

		while (char_token != '%') {
			switch (char_token) {
			case '#': {
				read_string_from_binary_file(fin, &string_buffer);

				path[0] = _str_p->get_str(string_buffer);
				_dbase->create_pull(path[0], data_base::flag::Btree);

				fin.read(&char_token, sizeof(char));
				break;
			}
			case '^': {
				read_string_from_binary_file(fin, &string_buffer);

				path[1] = _str_p->get_str(string_buffer);
				_dbase->create_scheme(path[1], path[0], data_base::flag::Btree);

				fin.read(&char_token, sizeof(char));

				break;
			}
			case '&': {
				read_string_from_binary_file(fin, &string_buffer);

				path[2] = _str_p->get_str(string_buffer);
				_dbase->create_collection(path[2], path[0], path[1], data_base::flag::Btree);

				fin.read(&char_token, sizeof(char));

				break;
			}
			case '!': {
				invoker my_invoker;

				fin.read(&char_token, sizeof(char));

				std::vector<collection*> vec_coll = _dbase->go_to_collection(path[0], path[1], path[2]);

				bool first_add = true;

				contest_info* member = nullptr;

				while (char_token == '@') {
					unsigned long long time;

					fin.read(reinterpret_cast<char*>(&time), sizeof(unsigned long long));

					read_string_from_binary_file(fin, &string_buffer);

					if (std::strcmp(string_buffer, "add_node_key") == 0) {
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
						bool cheating;

						fin.read(reinterpret_cast<char*>(&id_member), sizeof(int));
						read_string_from_binary_file(fin, &string_buffer);
						name = _str_p->get_str(string_buffer);
						read_string_from_binary_file(fin, &string_buffer);
						surname = _str_p->get_str(string_buffer);
						read_string_from_binary_file(fin, &string_buffer);
						patronymic = _str_p->get_str(string_buffer);
						read_string_from_binary_file(fin, &string_buffer);
						day_of_birthday = _str_p->get_str(string_buffer);
						read_string_from_binary_file(fin, &string_buffer);
						resume = _str_p->get_str(string_buffer);
						fin.read(reinterpret_cast<char*>(&id_hrmanager), sizeof(int));
						fin.read(reinterpret_cast<char*>(&id_contest), sizeof(int));
						read_string_from_binary_file(fin, &string_buffer);
						prog_lang = _str_p->get_str(string_buffer);
						fin.read(reinterpret_cast<char*>(&tasks_count), sizeof(int));
						fin.read(reinterpret_cast<char*>(&tasks_complete), sizeof(int));

						read_string_from_binary_file(fin, &string_buffer);
						if (std::strcmp(string_buffer, "true") == 0) {
							cheating = true;
						}
						else if (std::strcmp(string_buffer, "false") == 0) {
							cheating = false;
						}

						member = new contest_info(id_member, name, surname, patronymic, day_of_birthday,
							resume, id_hrmanager, id_contest, prog_lang, tasks_count, tasks_complete,
							cheating);


						//command* add_node_key_command = new add_node_key(member, collection, command_time);
						command* add_node_key_command;
						add_node_key_command = new add_node_key(member, vec_coll[0], time);
						try {
							member = vec_coll[0]->find(member);
						}
						catch (std::invalid_argument& e) {
							my_invoker.set_command(add_node_key_command);
							my_invoker.invoke();
						}
						for (int i = 1; i < vec_coll.size(); i++) {
							add_node_key_command = new add_node_key(member, vec_coll[i], time);
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
					}
					else if (std::strcmp(string_buffer, "update_node_key_name") == 0) {
						read_string_from_binary_file(fin, &string_buffer);
						update_node_key_name* update_node_key_command = new update_node_key_name(_str_p->get_str(string_buffer), time);

						my_invoker.add_command(*member, update_node_key_command);

					}
					else if (std::strcmp(string_buffer, "update_node_key_surname") == 0) {
						read_string_from_binary_file(fin, &string_buffer);
						update_node_key_surname* update_node_key_command = new update_node_key_surname(_str_p->get_str(string_buffer), time);

						my_invoker.add_command(*member, update_node_key_command);
					}
					else if (std::strcmp(string_buffer, "update_node_key_patronymic") == 0) {
						read_string_from_binary_file(fin, &string_buffer);
						update_node_key_patronymic* update_node_key_command = new update_node_key_patronymic(_str_p->get_str(string_buffer), time);

						my_invoker.add_command(*member, update_node_key_command);
					}
					else if (std::strcmp(string_buffer, "update_node_key_day_of_birthday") == 0) {
						read_string_from_binary_file(fin, &string_buffer);
						update_node_key_day_of_birthday* update_node_key_command = new update_node_key_day_of_birthday(_str_p->get_str(string_buffer), time);

						my_invoker.add_command(*member, update_node_key_command);
					}
					else if (std::strcmp(string_buffer, "update_node_key_id_hrmanager") == 0) {
						int id_hrmanager;
						fin.read(reinterpret_cast<char*>(&id_hrmanager), sizeof(int));
						update_node_key_id_hrmanager* update_node_key_command = new update_node_key_id_hrmanager(id_hrmanager, time);

						my_invoker.add_command(*member, update_node_key_command);
					}
					else if (std::strcmp(string_buffer, "update_node_key_prog_lang") == 0) {
						read_string_from_binary_file(fin, &string_buffer);
						update_node_key_prog_lang* update_node_key_command = new update_node_key_prog_lang(_str_p->get_str(string_buffer), time);

						my_invoker.add_command(*member, update_node_key_command);
					}
					else if (std::strcmp(string_buffer, "update_node_key_tasks_count") == 0) {
						int tasks_count;
						fin.read(reinterpret_cast<char*>(&tasks_count), sizeof(int));
						update_node_key_tasks_count* update_node_key_command = new update_node_key_tasks_count(tasks_count, time);

						my_invoker.add_command(*member, update_node_key_command);
					}
					else if (std::strcmp(string_buffer, "update_node_key_tasks_complete") == 0) {
						int tasks_count;
						fin.read(reinterpret_cast<char*>(&tasks_count), sizeof(int));
						update_node_key_tasks_count* update_node_key_command = new update_node_key_tasks_count(tasks_count, time);

						my_invoker.add_command(*member, update_node_key_command);
					}
					else if (std::strcmp(string_buffer, "update_node_key_cheating") == 0) {
						int cheating;
						fin.read(reinterpret_cast<char*>(&cheating), sizeof(bool));
						update_node_key_tasks_count* update_node_key_command = new update_node_key_tasks_count(cheating, time);

						my_invoker.add_command(*member, update_node_key_command);
					}
					else if (std::strcmp(string_buffer, "remove_node_key") == 0) {
						int id_member;
						int id_contest;
						fin.read(reinterpret_cast<char*>(&id_member), sizeof(int));
						fin.read(reinterpret_cast<char*>(&id_contest), sizeof(int));
						contest_info* key = new contest_info;
						key->set_id_member(id_member);
						key->set_id_contest(id_contest);
						remove_node_key* remove_node_key_command = new remove_node_key(key, vec_coll[0], time);
						my_invoker.add_command(*member, remove_node_key_command);

						delete key;
					}
					fin.read(&char_token, sizeof(char));
				}
				break;
			}


			}
		}

		fin.close();
		return _dbase;
	}

};



#endif DBASE_SAFE