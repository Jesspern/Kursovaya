#ifndef DATA_BASE
#define DATA_BASE

#include <iostream>

#include "Btree.cpp"
#include "AVLtree.cpp"
#include "SplayTree.cpp"

#include <memory>
#include <stdexcept>
#include "contest_info.h"
#include <vector>
#include "comp.h"

using collection = associative_container <contest_info*, contest_info*, comparer>;
using collection_resume = associative_container<contest_info*, contest_info*, comparer_resume>;
using collection_default = associative_container<contest_info*, contest_info*, comparer_id_member_id_contest>;
using scheme = associative_container<const std::string*, std::vector<collection*>*, string_const_ptr>;
using pull = associative_container<const std::string*, scheme*, string_const_ptr>;
using dbase = associative_container<const std::string*, pull*, string_const_ptr>;


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

	data_base(flag f, int b_const = 3);

	data_base();

	data_base(data_base&& other);

	data_base& operator=(data_base&& other);

	~data_base();

	dbase* get_dbase();

	pull* go_to_pull(const std::string* pull_name);

	scheme* go_to_scheme(const std::string* pull_name, const std::string* scheme_name);

	std::vector<collection*> go_to_collection(const std::string* pull_name, const std::string* scheme_name,
		const std::string* collection_name);

	contest_info* go_to_contest_info(collection* collection_name, contest_info* key);

	void create_pull(const std::string* name, flag f, int b_const = 3);

	void create_scheme(const std::string* name, const std::string* pull_name, flag f, int b_const = 3);

	void create_collection(const std::string* name, const std::string* pull_name, const std::string* sheme_name,
		flag f, int b_const = 3);

	void delete_pull(const std::string* name);

	void delete_scheme(const std::string* name, const std::string* pull);

	void delete_collection(const std::string* name, const std::string* pull, const std::string* sheme);

};
#endif
