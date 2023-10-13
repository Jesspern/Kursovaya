#ifndef DATA_BASE
#define DATA_BASE

#include <iostream>
#include "B-tree.cpp"
#include <memory>
#include <stdexcept>
#include "contest_info.h"

using collection = associative_container<contest_info* , contest_info*, comparer_id_member_id_contest>;
using scheme = associative_container<std::string, collection*, string_comparer>;
using pull = associative_container<std::string, scheme*, string_comparer>;
using dbase = associative_container<std::string, pull*, string_comparer>;


class data_base {

private:

	dbase* _dbase;

public:

	enum class flag {
		Btree,
		B_plus_tree,
		AVL,
		RB,
		Splay
	};

public:

	data_base(flag f, int b_const);

	data_base();

	data_base(data_base&& other);

	data_base& operator=(data_base && other);

	~data_base();

	pull* go_to_pull(std::string pull_name);

	scheme* go_to_scheme(std::string pull_name, std::string scheme_name);

	collection* go_to_collection(std::string pull_name, std::string scheme_name,
		std::string collection_name);

	contest_info* go_to_contest_info(collection* collection_name, std::pair<int, int> key);

	void create_pull(std::string name, flag f, int b_const = 3);

	void create_scheme(std::string name, std::string pull_name, flag f, int b_const = 3);

	void create_collection(std::string name, std::string pull_name, std::string sheme_name,
		flag f, int b_const = 3);

	void delete_pull(std::string name);

	void delete_scheme(std::string name, std::string pull);

	void delete_collection(std::string name, std::string pull, std::string sheme);

};
#endif
