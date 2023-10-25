#ifndef BTREE
#define BTREE


#include <iostream>
#include <vector>
#include "comparer.h"
#include <algorithm>
#include "associative_container.h"
#include <tuple>
#include <memory>
#include <type_traits>

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
class Btree final : public associative_container<tkey, tvalue, tkey_comparer>
{
private:

	struct bkeys {
		tkey key;
		tvalue value;
	};

	struct node {

		bool leaf = true;
		std::vector<bkeys> keys;
		std::vector<node*> children;
		node* parent = nullptr;

		~node() {
			for (int i = 0; i < keys.size(); i++) {
				/*if (typeid(keys[i].value) == typeid(std::vector)) {
					for (int j = 0; j < (keys[i].value).size(); j++) {
						delete (keys[i].value)[j];
					}
				}*/
				delete keys[i].value;
			}
		}

	};

private:

	node* _root;
	tkey_comparer _comp;
	int _t;

public:

	class infix_iterator final
	{

	private:

		node* _tree_root;
		int _index;

	private:

		explicit infix_iterator(Btree<tkey, tvalue, tkey_comparer> const& tree, bool flag);

	public:

		bool operator==(infix_iterator const& other) const;

		bool operator!=(infix_iterator const& other) const;

		infix_iterator& operator++();

		std::tuple<tkey, tvalue> operator*();

		friend infix_iterator Btree<tkey, tvalue, tkey_comparer>::infix_iterator_begin() const;

		friend infix_iterator Btree<tkey, tvalue, tkey_comparer>::infix_iterator_end() const;

	};

	infix_iterator infix_iterator_begin() const {
		return infix_iterator(*this, true);
	}

	infix_iterator infix_iterator_end() const {
		return infix_iterator(*this, false);
	}

private:

	tvalue findkey(tkey key, node* node);
	void insert_node(tkey key, tvalue& value, node* node);
	void separate(node* node);
	tvalue delete_key(tkey key, node* node);
	node* add_key(node* node);
	node* merge_brothers(node* left_brother, node* right_brother);
	node* max_elem(node* node);
	void delete_with_exchange(tkey key, node* node);
	tvalue swapkey(tkey key, tvalue& value, node* node);
	void deletenode(node* node);

public:

	Btree(int t) {
		_t = t;
		_root = nullptr;
	}
	Btree(Btree&& other) {

		_root = other._root;
		_t = other._t;

		other._root = nullptr;
		other._t = 0;

	}

	Btree(const Btree& other) {
		auto it_begin = other.infix_iterator_begin();
		auto it_end = other.infix_iterator_end();

		while (it_begin != it_end) {
			insert(std::get<0>(*it_begin), std::get<1>(*it_begin));
			++it_begin;
		}
	}

	~Btree();

	bool check_tree();
	tvalue find(tkey key);
	void insert(tkey key, tvalue& value);
	tvalue remove(tkey key);
	tvalue swap_value(tkey key, tvalue value);

};

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
Btree<tkey, tvalue, tkey_comparer>::infix_iterator::infix_iterator(Btree<tkey, tvalue, tkey_comparer> const& tree, bool flag)
{
	_tree_root = tree._root;
	_index = 0;
	if (flag) {
		while (_tree_root->children.size() != 0) {
			_tree_root = _tree_root->children[0];
		}
	}
	else {
		_tree_root = nullptr;
		_index = 0;
		/*while (_tree_root->children.size() != 0) {
			_tree_root = _tree_root->children[_tree_root->children.size() - 1];
		}
		_index = _tree_root->keys.size();*/
	}
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
bool Btree<tkey, tvalue, tkey_comparer>::infix_iterator::operator==(Btree<tkey, tvalue, tkey_comparer>::infix_iterator const& other) const
{
	if ((*this)._tree_root == other._tree_root and (*this)._index == other._index) {
		return true;
	}
	else {
		return false;
	}
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
bool Btree<tkey, tvalue, tkey_comparer>::infix_iterator::operator!=(infix_iterator const& other) const {
	if ((*this)._tree_root == other._tree_root and (*this)._index == other._index) {
		return false;
	}
	else {
		return true;
	}
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename Btree<tkey, tvalue, tkey_comparer>::infix_iterator& Btree<tkey, tvalue, tkey_comparer>::infix_iterator::operator++()
{
	if (_tree_root != nullptr) {
		if (_tree_root->children.size() != 0) {
			if (_index == _tree_root->children.size() - 1) {
				if (_tree_root->parent == nullptr) {
					this->_tree_root = nullptr;
					_index = 0;
					return *this;
				}
				for (int i = 0; i < _tree_root->parent->children.size(); i++) {
					if (_tree_root->parent->children[i] == _tree_root) {
						_index = i;
						break;
					}
				}
				_tree_root = _tree_root->parent;
			}
			_tree_root = _tree_root->children[++_index];
		}
		else {
			if (_index == _tree_root->keys.size() - 1) {
				// find index
				if (_tree_root->parent == nullptr) {
					this->_tree_root = nullptr;
					_index = 0;
					return *this;
				}
				for (int i = 0; i < _tree_root->parent->children.size(); i++) {
					if (_tree_root->parent->children[i] == _tree_root) {
						_index = i;
						break;
					}
				}
				_tree_root = _tree_root->parent;
			}
			_index++;
		}
	}
	else {
		return *this;
	}
	// next
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
std::tuple<tkey, tvalue> Btree<tkey, tvalue, tkey_comparer>::infix_iterator::operator*()
{
	//*const_cast<typename Btree<tkey, tvalue, tkey_comparer>::infix_iterator *>(this)
	std::tuple<tkey, tvalue> temp((this->_tree_root)->keys[this->_index].key,
		(this->_tree_root)->keys[this->_index].value);
	return temp;
}

//template<
//	typename tkey,
//	typename tvalue,
//	typename tkey_comparer>
//Btree<tkey, tvalue, tkey_comparer>::Btree(int t)
//{
//	_t = t;
//	_root = nullptr;
//}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
bool Btree<tkey, tvalue, tkey_comparer>::check_tree() {
	if (_root == nullptr) {
		return false;
	}
	return true;
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void Btree<tkey, tvalue, tkey_comparer>::deletenode(Btree<tkey, tvalue, tkey_comparer>::node* node)
{
	while (node != nullptr) {
		if (node->leaf) {
			if (node->parent != nullptr) {
				for (int i = 0; i < node->parent->children.size(); i++) {
					if (node->parent->children[i] == node) {
						node->parent->children.erase(node->parent->children.begin() + i);
						break;
					}
				}
			}
			/*for (int i = 0; i < node->keys.size(); i++) {
				delete (node->keys[i].value);
			}
			delete node;
			node = nullptr;*/
			node->~node();
			node = nullptr;
		}
		else {
			for (int i = 0; i < node->children.size(); i++) {
				deletenode(node->children[i]);
			}
		}
	}
}


template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
Btree<tkey, tvalue, tkey_comparer>::~Btree()
{
	if (_root != nullptr) {
		deletenode(_root);
	}
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
tvalue Btree<tkey, tvalue, tkey_comparer>::findkey(tkey key, Btree<tkey, tvalue, tkey_comparer>::node* node)
{
	if (node != nullptr) {
		if (node->leaf == false) {
			int i;
			for (i = 0; i < node->keys.size(); i++) {
				if (_comp.comparate(node->keys[i].key, key) == 0) {
					return node->keys[i].value;
				}
				else if (_comp.comparate(node->keys[i].key, key) == 1) {
					return findkey(key, node->children[i]);
				}
			}
			return findkey(key, node->children[i]);
		}
		else {
			for (int i = 0; i < node->keys.size(); i++) {
				if (_comp.comparate(node->keys[i].key, key) == 0) {
					return node->keys[i].value;
				}
			}
			throw std::invalid_argument("ID is not correct");
		}
	}
	else {
		throw std::invalid_argument("ID is not correct");
	}

}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
tvalue Btree<tkey, tvalue, tkey_comparer>::find(tkey key)
{
	try {
		tvalue value = findkey(key, _root);
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("ID is not correct");
	}
	return findkey(key, _root);
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void Btree<tkey, tvalue, tkey_comparer>::insert_node(tkey key, tvalue& value, Btree<tkey, tvalue, tkey_comparer>::node* node)
{
	Btree<tkey, tvalue, tkey_comparer>::bkeys temp;
	temp.key = key;
	temp.value = value;
	node->keys.push_back(temp);
	//std::sort(node->keys.begin(), node->keys.end(), comparer);
	std::sort(node->keys.begin(), node->keys.end(),
		[](Btree<tkey, tvalue, tkey_comparer>::bkeys& first, Btree<tkey, tvalue, tkey_comparer>::bkeys& second)
		{return first.key < second.key; });
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void Btree<tkey, tvalue, tkey_comparer>::separate(Btree<tkey, tvalue, tkey_comparer>::node* node)
{
	if (node->keys.size() < _t * 2 - 1) {
		return;
	}

	Btree<tkey, tvalue, tkey_comparer>::node* child_left = new Btree<tkey, tvalue, tkey_comparer>::node;
	if (node->children.size() != 0) {

		for (int i = 0; i < _t - 1; i++) {
			child_left->keys.push_back(node->keys[i]);
			child_left->children.push_back(node->children[i]);
			child_left->children[i]->parent = child_left;
			if (i == _t - 2) {
				child_left->children.push_back(node->children[i + 1]);
				child_left->children[i + 1]->parent = child_left;
			}
		}
		child_left->leaf = false;
	}
	else {
		for (int i = 0; i < _t - 1; i++) {
			child_left->keys.push_back(node->keys[i]);
		}
		child_left->leaf = true;
	}

	Btree<tkey, tvalue, tkey_comparer>::node* child_right = new Btree<tkey, tvalue, tkey_comparer>::node;
	if (node->children.size() != 0) {
		for (int i = 0; i < _t - 1; i++) {
			child_right->keys.push_back(node->keys[i + _t]);
			child_right->children.push_back(node->children[i + _t]);
			child_right->children[i]->parent = child_right;
			if (i == _t - 2) {
				child_right->children.push_back(node->children[i + _t + 1]);
				child_right->children[i + 1]->parent = child_right;
			}
		}
		child_right->leaf = false;
	}
	else {
		for (int i = 0; i < _t - 1; i++) {
			child_right->keys.push_back(node->keys[i + _t]);
		}
		child_right->leaf = true;
	}

	if (node->parent == nullptr) {
		Btree<tkey, tvalue, tkey_comparer>::node* temp = new Btree<tkey, tvalue, tkey_comparer>::node;
		temp->keys.push_back(node->keys[_t - 1]);
		temp->children.push_back(child_left);
		temp->children.push_back(child_right);
		temp->leaf = false;
		temp->parent = nullptr;
		_root = temp;
		child_right->parent = _root;
		child_left->parent = _root;
		delete node;
	}
	else {
		insert_node(node->keys[_t - 1].key, node->keys[_t - 1].value, node->parent);
		for (int i = 0; i < node->parent->keys.size(); i++) {
			if (_comp.comparate(node->parent->keys[i].key, node->keys[_t - 1].key) == 0) {
				if (i == 0) {
					node->parent->children.insert(node->parent->children.begin() + i, child_left);
					node->parent->children[i + 1] = child_right;
				}
				else {
					node->parent->children[i] = child_left;
					node->parent->children.insert(node->parent->children.begin() + i + 1, child_right);
				}
				//node->parent->children[i] = child_left;
				//node->parent->children[i + 1] = child_right;
				break;
			}
		}
		child_right->parent = node->parent;
		child_left->parent = node->parent;
		node->parent->leaf = false;
	}
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void Btree<tkey, tvalue, tkey_comparer>::insert(tkey key, tvalue& value)
{
	// check if this key exist
	if (_root == nullptr) {
		node* ins = new node;
		Btree<tkey, tvalue, tkey_comparer>::bkeys temp_node;
		temp_node.key = key;
		temp_node.value = value;
		//temp_node.value = std::move(value);
		ins->keys.push_back(temp_node);
		_root = ins;
	}
	else {
		node* _ptr = _root;
		while (_ptr->leaf == false) {
			for (int i = 0; i < _ptr->keys.size(); i++) {
				if (_comp.comparate(_ptr->keys[i].key, key) == 1) {
					_ptr = _ptr->children[i];
					break;
				}
				if (_ptr->keys.size() == i + 1) {
					_ptr = _ptr->children[i + 1];
					break;
				}
			}
		}
		insert_node(key, value, _ptr);
		while (_ptr->keys.size() == 2 * _t - 1) {
			if (_ptr == _root) {
				// devide _ptr
				separate(_ptr);
				break;
			}
			else {
				// devide _ptr
				separate(_ptr);
				Btree<tkey, tvalue, tkey_comparer>::node* temp = _ptr;
				_ptr = _ptr->parent;
				delete temp;
			}
		}
	}
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
tvalue Btree<tkey, tvalue, tkey_comparer>::delete_key(tkey key, Btree<tkey, tvalue, tkey_comparer>::node* node)
{
	for (int i = 0; i < node->keys.size(); i++) {
		if (_comp.comparate(node->keys[i].key, key) == 0) {
			tvalue& value = node->keys[i].value;
			node->keys.erase(node->keys.begin() + i);
			return value;
		}
	}
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename Btree<tkey, tvalue, tkey_comparer>::node* Btree<tkey, tvalue, tkey_comparer>::merge_brothers(Btree<tkey, tvalue, tkey_comparer>::node* left_brother, Btree<tkey, tvalue, tkey_comparer>::node* right_brother)
{
	Btree<tkey, tvalue, tkey_comparer>::node* parent = left_brother->parent;
	if (parent->keys.size() == 1 and parent == _root) {
		Btree<tkey, tvalue, tkey_comparer>::node* two_brothers = new Btree<tkey, tvalue, tkey_comparer>::node;
		if (left_brother->leaf and right_brother->leaf) {
			for (int j = 0; j < 2 * _t - 1; j++) {
				if (j < _t - 1) {
					two_brothers->keys.push_back(left_brother->keys[j]);

				}
				else if (j == _t - 1) {
					two_brothers->keys.push_back(parent->keys[0]);
				}
				else {
					two_brothers->keys.push_back(right_brother->keys[j - _t]);
				}
			}
			two_brothers->parent = nullptr;
			two_brothers->leaf = true;
			_root = two_brothers;
			delete parent;
			delete left_brother;
			delete right_brother;
		}
		else {
			for (int j = 0; j < 2 * _t - 1; j++) {
				if (j < _t - 1) {
					two_brothers->keys.push_back(left_brother->keys[j]);
					two_brothers->children.push_back(left_brother->children[j]);

				}
				else if (j == _t - 1) {
					two_brothers->keys.push_back(parent->keys[0]);
					two_brothers->children.push_back(left_brother->children[j]);
				}
				else {
					two_brothers->keys.push_back(right_brother->keys[j - _t]);
					two_brothers->children.push_back(right_brother->children[j - _t]);
					if (j == 2 * _t - 2) {
						two_brothers->children.push_back(right_brother->children[j + 1 - _t]);
						two_brothers->children[j + 1]->parent = two_brothers;
					}
				}
				two_brothers->children[j]->parent = two_brothers;
			}
			two_brothers->parent = nullptr;
			two_brothers->leaf = false;
			_root = two_brothers;
			delete parent;
			delete left_brother;
			delete right_brother;
		}
		return two_brothers;
	}
	else {
		for (int i = 0; i < parent->children.size(); i++) {
			if (parent->children[i] == left_brother) {
				// merge
				Btree<tkey, tvalue, tkey_comparer>::node* two_brothers = new Btree<tkey, tvalue, tkey_comparer>::node;
				if (left_brother->leaf and right_brother->leaf) {
					for (int j = 0; j < 2 * _t - 1; j++) {
						if (j < _t - 1) {
							two_brothers->keys.push_back(left_brother->keys[j]);

						}
						else if (j == _t - 1) {
							two_brothers->keys.push_back(parent->keys[i]);
						}
						else {
							two_brothers->keys.push_back(right_brother->keys[j - _t]);
						}
					}

					two_brothers->parent = parent;
					two_brothers->leaf = true;
					parent->children[i] = two_brothers;
					parent->keys.erase(parent->keys.begin() + i);
					parent->children.erase(parent->children.begin() + i + 1);
					delete left_brother;
					delete right_brother;
				}
				else {
					for (int j = 0; j < 2 * _t - 1; j++) {
						if (j < _t - 1) {
							two_brothers->keys.push_back(left_brother->keys[j]);
							two_brothers->children.push_back(left_brother->children[j]);

						}
						else if (j == _t - 1) {
							two_brothers->keys.push_back(parent->keys[i]);
							two_brothers->children.push_back(left_brother->children[j]);
						}
						else {
							two_brothers->keys.push_back(right_brother->keys[j - _t]);
							two_brothers->children.push_back(right_brother->children[j - _t]);
							if (j == 2 * _t - 2) {
								two_brothers->children.push_back(right_brother->children[j + 1 - _t]);
								two_brothers->children[j + 1]->parent = two_brothers;
							}
						}
						two_brothers->children[j]->parent = two_brothers;
					}
					two_brothers->parent = parent;
					two_brothers->leaf = false;
					parent->children[i] = two_brothers;
					parent->keys.erase(parent->keys.begin() + i);
					parent->children.erase(parent->children.begin() + i + 1);
					delete left_brother;
					delete right_brother;
				}
				return two_brothers;
			}
		}
	}
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename Btree<tkey, tvalue, tkey_comparer>::node* Btree<tkey, tvalue, tkey_comparer>::add_key(Btree<tkey, tvalue, tkey_comparer>::node* node)
{
	for (int i = 0; i < node->parent->children.size(); i++) {
		if (node->parent->children[i] == node) {
			if (i == 0) {
				// left node
				Btree<tkey, tvalue, tkey_comparer>::node* right_brother = node->parent->children[i + 1];
				if (right_brother->keys.size() >= _t) {
					// steal node
					if (right_brother->leaf) {
						node->keys.push_back(node->parent->keys[i]);
						node->parent->keys[i] = right_brother->keys[0];

						right_brother->keys.erase(right_brother->keys.begin());
					}
					else {
						node->keys.push_back(node->parent->keys[i]);
						node->children.push_back(right_brother->children[0]);
						node->parent->keys[i] = right_brother->keys[0];

						right_brother->keys.erase(right_brother->keys.begin());
						right_brother->children.erase(right_brother->children.begin());
					}

					return node;
				}
				else {
					// merge brothers
					node = merge_brothers(node, right_brother);

					return node;
				}
			}
			else if (i == node->parent->children.size() - 1) {
				// right node
				Btree<tkey, tvalue, tkey_comparer>::node* left_brother = node->parent->children[i - 1];
				if (left_brother->keys.size() >= _t) {
					// steal node
					if (left_brother->leaf) {
						node->keys.insert(node->keys.begin(), node->parent->keys[i - 1]);
						node->parent->keys[i - 1] = left_brother->keys[left_brother->keys.size() - 1];

						left_brother->keys.erase(left_brother->keys.end() - 1);
					}
					else {
						node->keys.insert(node->keys.begin(), node->parent->keys[i - 1]);
						node->children.insert(node->children.begin(), left_brother->children[left_brother->children.size() - 1]);
						node->parent->keys[i - 1] = left_brother->keys[left_brother->keys.size() - 1];

						left_brother->keys.erase(left_brother->keys.end() - 1);
						left_brother->children.erase(left_brother->children.end() - 1);
					}
					return node;
				}
				else {
					// merge brothers
					node = merge_brothers(left_brother, node);

					return node;
				}
			}
			else {
				Btree<tkey, tvalue, tkey_comparer>::node* left_brother = node->parent->children[i - 1];
				if (left_brother->keys.size() >= _t) {
					// steal node
					//cheack for leaf
					if (left_brother->leaf) {
						node->keys.insert(node->keys.begin(), node->parent->keys[i - 1]);
						node->parent->keys[i - 1] = left_brother->keys[left_brother->keys.size() - 1];

						left_brother->keys.erase(left_brother->keys.end() - 1);
					}
					else {
						node->keys.insert(node->keys.begin(), node->parent->keys[i - 1]);
						node->children.insert(node->children.begin(), left_brother->children[left_brother->children.size() - 1]);
						node->parent->keys[i - 1] = left_brother->keys[left_brother->keys.size() - 1];

						left_brother->keys.erase(left_brother->keys.end() - 1);
						left_brother->children.erase(left_brother->children.end() - 1);
					}


					return node;
				}
				Btree<tkey, tvalue, tkey_comparer>::node* right_brother = node->parent->children[i + 1];
				if (right_brother->keys.size() >= _t) {
					// steal node
					if (right_brother->leaf) {
						node->keys.push_back(node->parent->keys[i]);
						node->parent->keys[i] = right_brother->keys[0];

						right_brother->keys.erase(right_brother->keys.begin());
					}
					else {
						node->keys.push_back(node->parent->keys[i]);
						node->children.push_back(right_brother->children[0]);
						node->parent->keys[i] = right_brother->keys[0];

						right_brother->keys.erase(right_brother->keys.begin());
						right_brother->children.erase(right_brother->children.begin());
					}

					return node;
				}
				if (left_brother->keys.size() < _t and right_brother->keys.size() < _t) {
					// merge brothers
					node = merge_brothers(left_brother, node);

					return node;
				}
			}
		}
	}
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename Btree<tkey, tvalue, tkey_comparer>::node* Btree<tkey, tvalue, tkey_comparer>::max_elem(Btree<tkey, tvalue, tkey_comparer>::node* node)
{
	if (node->leaf == false) {
		if (node->keys.size() < _t) {
			node = add_key(node);
		}
		return max_elem(node->children[node->children.size() - 1]);
	}
	return node;
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void Btree<tkey, tvalue, tkey_comparer>::delete_with_exchange(tkey key, Btree<tkey, tvalue, tkey_comparer>::node* node)
{
	//find node
	for (int i = 0; i < node->keys.size(); i++) {
		if (_comp.comparate(node->keys[i].key, key) == 0) {
			Btree<tkey, tvalue, tkey_comparer>::node* last = max_elem(node->children[i]);
			if (last->keys.size() < _t) {
				last = add_key(last);
			}
			for (int j = 0; j < node->keys.size(); j++) {
				if (_comp.comparate(node->keys[j].key, key) == 0) {
					//change value
					node->keys[j] = last->keys[last->keys.size() - 1];
					break;
				}
			}

			//delete node
			last->keys.pop_back();
			break;
		}
	}
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
tvalue Btree<tkey, tvalue, tkey_comparer>::remove(tkey key)
{
	try {
		tvalue value = find(key);
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("ID is not correct");
	}
	Btree<tkey, tvalue, tkey_comparer>::node* temp = _root;
	for (int i = 0; i < temp->keys.size(); i++) {
		if (temp->keys.size() < _t and temp != _root) {
			//add key to node
			temp = add_key(temp);
		}
		if (_comp.comparate(temp->keys[i].key, key) == 0) {
			if (temp == _root) {
				//delete node
				if (temp->leaf) {
					delete_key(key, temp);
				}
				else {
					if (temp->keys.size() == 1) {
						_root = merge_brothers(temp->children[0], temp->children[1]);
						delete_with_exchange(key, temp);
					}
					else {
						delete_with_exchange(key, temp);
					}
				}
			}
			else {
				if (temp->keys.size() >= _t) {
					if (temp->leaf) {
						//just delete key
						delete_key(key, temp);
					}
					else {
						//find exchange and delete key
						delete_with_exchange(key, temp);
					}
				}
				else {
					//add key to node and then delete key
					temp = add_key(temp);
					delete_with_exchange(key, temp);
				}
			}

			break;
		}
		else if (_comp.comparate(temp->keys[i].key, key) == 1) {
			temp = temp->children[i];
			i = -1;
		}
		else if (i == temp->keys.size() - 1) {
			temp = temp->children[i + 1];
			i = -1;
		}
	}
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
tvalue Btree<tkey, tvalue, tkey_comparer>::swapkey(tkey key, tvalue& value, Btree<tkey, tvalue, tkey_comparer>::node* node)
{
	if (node != nullptr) {
		if (node->leaf == false) {
			int i;
			for (i = 0; i < node->keys.size(); i++) {
				if (_comp.comparate(node->keys[i].key, key) == 0) {
					tvalue temp_value = node->keys[i].value;
					node->keys[i].value = value;
					return temp_value;
				}
				else if (_comp.comparate(node->keys[i].key, key) == 1) {
					return swapkey(key, value, node->children[i]);
				}
			}
			return swapkey(key, value, node->children[i]);
		}
		else {
			for (int i = 0; i < node->keys.size(); i++) {
				if (_comp.comparate(node->keys[i].key, key) == 0) {
					tvalue temp_value = node->keys[i].value;
					node->keys[i].value = value;
					return temp_value;
				}
			}
			throw std::invalid_argument("Id is not exist");
		}
	}
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
tvalue Btree<tkey, tvalue, tkey_comparer>::swap_value(tkey key, tvalue value)
{
	try {
		tvalue _value = find(key);
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("ID is not correct");
	}
	tvalue _value;
	try {
		_value = swapkey(key, value, _root);
	}
	catch (std::invalid_argument&) {
		throw std::invalid_argument("Id is not correct in swap");
	}
	return _value;
}

#endif // !1