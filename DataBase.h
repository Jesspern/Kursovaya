#ifndef DATA_BASE
#define DATA_BASE

#include <iostream>
#include "B-tree.cpp"
#include <memory>
#include <stdexcept>
#include "contest_info.h"

using collection = associative_container<std::pair<int, int>, contest_info*, comparer>;
using scheme = associative_container<std::string, collection*, comparer>;
using pull = associative_container<std::string, scheme*, comparer>;
using dbase = associative_container<std::string, pull*, comparer>;


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

	void create_pull(std::string name, flag f, int b_const = 3);

	void create_scheme(std::string name, std::string pull_name, flag f, int b_const = 3);

	void create_collection(std::string name, std::string pull_name, std::string sheme_name,
		flag f, int b_const = 3);

	void delete_pull(std::string name);

	void delete_scheme(std::string name, std::string pull);

	void delete_collection(std::string name, std::string pull, std::string sheme);

};
#endif
