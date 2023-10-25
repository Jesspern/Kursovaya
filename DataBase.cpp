#include "DataBase.h"

data_base::data_base()
{
	_dbase = nullptr;
}

data_base::data_base(data_base&& other)
{
	_dbase = other._dbase;

	other._dbase = nullptr;
}

data_base& data_base::operator=(data_base&& other)
{
	_dbase = other._dbase;

	other._dbase = nullptr;

	return *this;
}	

data_base::data_base(data_base::flag f, int b_const)
{
	switch (f)
	{
	case flag::Btree:
		_dbase = new Btree<const std::string*, pull*, string_const_ptr>(b_const);
		break;

	case flag::AVL:
		_dbase = new avltree<const std::string*, pull*, string_const_ptr>();
		break;

	case flag::Splay:
		_dbase = new splay_tree<const std::string*, pull*, string_const_ptr>();
		break;

	default:
		throw std::invalid_argument("Flag is not correct");
	}

}

data_base::~data_base()
{
	if (_dbase != nullptr) {
		delete _dbase;
		_dbase = nullptr;
	}
}

dbase* data_base::get_dbase() {
	return _dbase;
}

pull* data_base::go_to_pull(const std::string* pull_name)
{
	pull* temp_pull;
	try {
		temp_pull = _dbase->find(pull_name);
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("Wrong name of pull");
	}
	return temp_pull;
}

scheme* data_base::go_to_scheme(const std::string* pull_name, const std::string* scheme_name)
{
	pull* temp_pull;
	try {
		temp_pull = _dbase->find(pull_name);
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("Wrong name of pull");
	}
	scheme* temp_scheme;
	try {
		temp_scheme = temp_pull->find(scheme_name);
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("Wrong name of scheme");
	}
	return temp_scheme;
}

std::vector<collection*> data_base::go_to_collection(const std::string* pull_name, const std::string* scheme_name,
	const std::string* collection_name)
{
	pull* temp_pull;
	try {
		temp_pull = _dbase->find(pull_name);
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("Wrong name of pull");
	}
	scheme* temp_scheme;
	try {
		temp_scheme = temp_pull->find(scheme_name);
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("Wrong name of scheme");
	}
	std::vector<collection*> temp_collection;
	try {
		temp_collection = *(temp_scheme->find(collection_name));
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("Wrong name of collection");
	}
	return temp_collection;
}

contest_info* data_base::go_to_contest_info(collection* collection_name, contest_info* key)
{
	contest_info* contest;
	try {
		contest = collection_name->find(key);
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("Wrong name of collection");
	}
	return contest;
}

void data_base::create_pull(const std::string* name, data_base::flag f, int b_const)
{
	pull* pull1;

	try {
		go_to_pull(name);
	}
	catch (std::invalid_argument& e) {
		switch (f)
		{
		case flag::Btree:
			pull1 = new Btree<const std::string*, scheme*, string_const_ptr>(Btree<const std::string*, scheme*, string_const_ptr>(b_const));
			break;

		case flag::AVL:
			pull1 = new avltree<const std::string*, scheme*, string_const_ptr>(avltree<const std::string*, scheme*, string_const_ptr>());
			break;

		case flag::Splay:
			pull1 = new splay_tree<const std::string*, scheme*, string_const_ptr>(splay_tree<const std::string*, scheme*, string_const_ptr>());
			break;

		default:
			throw std::invalid_argument("Flag is not correct");
		}
		_dbase->insert(name, pull1);
		return;
	}
	throw std::invalid_argument("Pool is exist");
}

void data_base::create_scheme(const std::string* name, const std::string* pull_name, data_base::flag f, int b_const)
{
	pull* temp_pull;
	try {
		temp_pull = go_to_pull(pull_name);
	}
	catch (std::invalid_argument& e) {
		throw e;
	}
	try {
		go_to_scheme(pull_name, name);
	}
	catch (std::invalid_argument& e) {
		scheme* scheme1;
		switch (f)
		{
		case flag::Btree:
			scheme1 = new Btree<const std::string*, std::vector<collection*>*, string_const_ptr>(b_const);
			break;

		case flag::AVL:
			scheme1 = new avltree<const std::string*, std::vector<collection*>*, string_const_ptr>();
			break;

		case flag::Splay:
			scheme1 = new splay_tree<const std::string*, std::vector<collection*>*, string_const_ptr>();
			break;

		default:
			throw std::invalid_argument("Flag is not correct");
		}
		temp_pull->insert(name, scheme1);
		return;
	}
	throw std::invalid_argument("Scheme is exist");
}

void data_base::create_collection(const std::string* name, const std::string* pull_name,
	const std::string* scheme_name, flag f, int b_const)
{
	scheme* scheme1;
	try {
		scheme1 = go_to_scheme(pull_name, scheme_name);
	}
	catch (std::invalid_argument& e) {
		throw e;
	}
	try {
		go_to_collection(pull_name, scheme_name, name);
	}
	catch (std::invalid_argument& e) {
		collection_default* temp_collection_def;
		collection_resume* temp_collection_res;
		switch (f)
		{
		case flag::Btree:
			temp_collection_def = new Btree<contest_info*, contest_info*, comparer_id_member_id_contest>(b_const);
			temp_collection_res = new Btree<contest_info*, contest_info*, comparer_resume>(b_const);
			break;

		case flag::AVL:
			temp_collection_def = new avltree<contest_info*, contest_info*, comparer_id_member_id_contest>();
			temp_collection_res = new avltree<contest_info*, contest_info*, comparer_resume>();
			break;

		case flag::Splay:
			temp_collection_def = new splay_tree<contest_info*, contest_info*, comparer_id_member_id_contest>();
			temp_collection_res = new splay_tree<contest_info*, contest_info*, comparer_resume>();
			break;
		default:
			throw std::invalid_argument("Flag is not correct");
		}
		//std::vector<collection*> colls = { (collection*)temp_collection_def, (collection*)temp_collection_res };
		std::vector<collection*>* colls = new std::vector<collection*>;
		*colls = { (collection*)temp_collection_def, (collection*)temp_collection_res };
		scheme1->insert(name, colls);
		return;
	}
	throw std::invalid_argument("Collection is exist");
}

void data_base::delete_pull(const std::string* name)
{
	try {
		_dbase->remove(name);
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("Name of pool is not correct");
	}
}

void data_base::delete_scheme(const std::string* name, const std::string* pull_name)
{
	pull* pull1;
	try {
		pull1 = go_to_pull(pull_name);
	}
	catch (std::invalid_argument& e) {
		throw e;
	}
	try {
		pull1->remove(name);
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("Name of scheme is not correct");
	}
}

void data_base::delete_collection(const std::string* name, const std::string* pull_name,
	const std::string* scheme_name)
{
	scheme* scheme1;
	try {
		scheme1 = go_to_scheme(pull_name, scheme_name);
	}
	catch (std::invalid_argument& e) {
		throw e;
	}
	try {
		scheme1->remove(name);
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("Name of collection is not correct");
	}
}