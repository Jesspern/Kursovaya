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

data_base& data_base::operator=(data_base && other)
{
	_dbase = other._dbase;

	other._dbase = nullptr;

	return *this;
}

data_base::data_base(data_base::flag f, int b_const = 3)
{
	switch (f)
	{
	case flag::Btree:
		_dbase = new Btree<std::string, pull *, string_comparer>(b_const);
		break;

	case flag::B_plus_tree:

		break;

	case flag::AVL:

		break;

	case flag::RB:

		break;

	case flag::Splay:

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

pull* data_base::go_to_pull(std::string pull_name)
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

scheme* data_base::go_to_scheme(std::string pull_name, std::string scheme_name)
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

collection* data_base::go_to_collection(std::string pull_name, std::string scheme_name,
	std::string collection_name)
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
	collection* temp_collection;
	try {
		temp_collection = temp_scheme->find(collection_name);
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("Wrong name of collection");
	}
	return temp_collection;
}

contest_info* data_base::go_to_contest_info(collection* collection_name, std::pair<int, int> key) 
{
	contest_info* contest;
	contest_info* key_contest = new contest_info;
	key_contest->set_id_member(key.first);
	key_contest->set_id_contest(key.second);
	try {
		contest = collection_name->find(key_contest);
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("Wrong name of collection");
	}
	delete key_contest;
	return contest;
}

void data_base::create_pull(std::string name, data_base::flag f, int b_const)
{
	pull* pull1;
	switch (f)
	{
	case flag::Btree:
		pull1 = new Btree<std::string, scheme*, string_comparer>(Btree<std::string, scheme*, string_comparer>(b_const));
		break;

	case flag::B_plus_tree:
		pull1 = new Btree<std::string, scheme*, string_comparer>(Btree<std::string, scheme*, string_comparer>(b_const));
		break;

	case flag::AVL:
		pull1 = new Btree<std::string, scheme*, string_comparer>(Btree<std::string, scheme*, string_comparer>(b_const));
		break;

	case flag::RB:
		pull1 = new Btree<std::string, scheme*, string_comparer>(Btree<std::string, scheme*, string_comparer>(b_const));
		break;

	case flag::Splay:
		pull1 = new Btree<std::string, scheme*, string_comparer>(Btree<std::string, scheme*, string_comparer>(b_const));
		break;

	default:
		throw std::invalid_argument("Flag is not correct");
	}
	_dbase->insert(name, pull1);
}

void data_base::create_scheme(std::string name, std::string pull_name, data_base::flag f, int b_const)
{
	pull* temp_pull;
	try {
		temp_pull = go_to_pull(pull_name);
	}
	catch (std::invalid_argument& e) {
		std::cerr << e.what();
		return;
	}
	scheme* scheme1;
	switch (f)
	{
	case flag::Btree:
		scheme1 = new Btree<std::string, collection*, string_comparer>(b_const);
		break;

	case flag::B_plus_tree:
		scheme1 = new Btree<std::string, collection*, string_comparer>(b_const);
		break;

	case flag::AVL:
		scheme1 = new Btree<std::string, collection*, string_comparer>(b_const);
		break;

	case flag::RB:
		scheme1 = new Btree<std::string, collection*, string_comparer>(b_const);
		break;

	case flag::Splay:
		scheme1 = new Btree<std::string, collection*, string_comparer>(b_const);
		break;

	default:
		throw std::invalid_argument("Flag is not correct");
	}
	temp_pull->insert(name, scheme1);
}

void data_base::create_collection(std::string name, std::string pull_name,
	std::string scheme_name, flag f, int b_const)
{
	scheme* scheme1;
	try {
		scheme1 = go_to_scheme(pull_name, scheme_name);
	}
	catch (std::invalid_argument& e) {
		std::cerr << e.what();
		return;
	}
	collection* temp_collection;
	switch (f)
	{
	case flag::Btree:
		temp_collection = new Btree<contest_info*, contest_info*, comparer_id_member_id_contest>(b_const);
		break;

	case flag::B_plus_tree:
		temp_collection = new Btree<contest_info*, contest_info*, comparer_id_member_id_contest>(b_const);
		break;

	case flag::AVL:
		temp_collection = new Btree<contest_info*, contest_info*, comparer_id_member_id_contest>(b_const);
		break;

	case flag::RB:
		temp_collection = new Btree<contest_info*, contest_info*, comparer_id_member_id_contest>(b_const);
		break;

	case flag::Splay:
		temp_collection = new Btree<contest_info* , contest_info*, comparer_id_member_id_contest>(b_const);
		break;
	default:
		throw std::invalid_argument("Flag is not correct");
	}
	scheme1->insert(name, temp_collection);
}

void data_base::delete_pull(std::string name)
{
	try {
		_dbase->remove(name);
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("Name of pool is not correct");
	}
}

void data_base::delete_scheme(std::string name, std::string pull_name)
{
	pull* pull1;
	try {
		pull1 = go_to_pull(pull_name);
	}
	catch (std::invalid_argument& e) {
		std::cerr << e.what();
		return;
	}
	try {
		pull1->remove(name);
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("Name of pool is not correct");
	}
}

void data_base::delete_collection(std::string name, std::string pull_name,
	std::string scheme_name)
{
	scheme* scheme1;
	try {
		scheme1 = go_to_scheme(pull_name, scheme_name);
	}
	catch (std::invalid_argument& e) {
		std::cerr << e.what();
		return;
	}
	try {
		scheme1->remove(name);
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("Name of pool is not correct");
	}
}