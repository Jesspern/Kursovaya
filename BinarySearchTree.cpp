#ifndef BINARYSEARCHTREE
#define BINARYSEARCHTREE

#include "associative_container.h"
#include <stack>
#include <stdexcept>
#include "comparer.h"
#include <tuple>

#include <iostream>
#include <algorithm>
#include <memory>
#include <type_traits>

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
class binary_search_tree : public associative_container<tkey, tvalue, tkey_comparer>
{
protected:

	struct tree_node {
		tkey key;
		tvalue value;
		tree_node* right_node;
		tree_node* left_node;

		virtual ~tree_node() noexcept = default;

	};

	tree_node* _root;
	tkey_comparer _comp;

public:

	binary_search_tree() {
		_root = nullptr;
	}

	~binary_search_tree() {
		//delete tree;
	}

public:

	class infix_iterator final {

	private:

		std::stack<tree_node*> _way;

	private:

		explicit infix_iterator(binary_search_tree<tkey, tvalue, tkey_comparer> const& tree, bool flag) {
			tree_node* node = tree._root;
			if (flag) {
				_way.push(node);
				while (node->left_node != nullptr) {
					node = node->left_node;
					_way.push(node);
				}
			}
			else {
				_way.push(nullptr);
			}
		}

	public:

		bool operator==(infix_iterator const& other) const {
			if ((this->_way.top()) == other._way.top()) {
				return true;
			}
			else {
				return false;
			}
		}

		bool operator!=(infix_iterator const& other) const {
			if ((this->_way.top()) == other._way.top()) {
				return false;
			}
			else {
				return true;
			}
		}

		infix_iterator& operator++() {
			if (is_end_iterator()) {
				return *this;
			}
			tree_node* node_return = _way.top();
			tree_node* node_next = node_return->right_node;
			if (node_next != nullptr) {
				_way.push(node_next);
				while (node_next->left_node != nullptr) {
					node_next = node_next->left_node;
					_way.push(node_next);
				}
			}
			else {
				_way.pop();
				if (_way.empty()) {
					_way.push(nullptr);
					return *this;
				}
				else {
					tree_node* current_node = node_return;
					tree_node* parent_node = _way.top();
					while (parent_node->right_node == current_node) {
						_way.pop();
						if (_way.empty()) {
							_way.push(nullptr);
							break;
						}
						current_node = parent_node;
						parent_node = _way.top();
					}
				}
			}
			return *this;
		}

		bool is_end_iterator() const noexcept {
			return _way.top() == nullptr;
		}

		std::tuple<tkey, tvalue> operator*() {
			std::tuple<tkey, tvalue> temp((_way.top())->key,
				(_way.top())->value);
			return temp;
		}

		friend infix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator_begin() const;

		friend infix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator_end() const;

	};

	infix_iterator infix_iterator_begin() const {
		return infix_iterator(*this, true);
	}

	infix_iterator infix_iterator_end() const {
		return infix_iterator(*this, false);
	}

private:

	virtual void before_insert() {}

	virtual void after_insert(std::stack<tree_node*> way) {}

	virtual void inserted_after(
		std::stack<tree_node*> way,
		tree_node* node
	) {}

	tree_node* insert_key(tkey key, tvalue& value, std::stack<tree_node*>& _way) {
		tree_node* node_insert = findkey(key, _root, _way);
		if (node_insert == nullptr) {
			node_insert = new tree_node;
			node_insert->key = key;
			node_insert->value = value;
			node_insert->left_node = nullptr;
			node_insert->right_node = nullptr;
			_way.pop();
			tree_node* parent = _way.top();
			_way.push(node_insert);
			if (_comp.comparate(key, parent->key) == 1) {
				parent->right_node = node_insert;
			}
			else {
				parent->left_node = node_insert;
			}
		}
		else {
			throw std::invalid_argument("This key already exists");
		}
		return node_insert;
	}

	virtual void before_find() {}

	virtual void after_find(
		std::stack<tree_node*> way,
		tree_node* node
	) {}

	tree_node* findkey(tkey key, tree_node* node, std::stack<tree_node*>& _way) {
		tree_node* temp_find = _root;
		while (temp_find != nullptr) {
			_way.push(temp_find);
			if (_comp.comparate(key, temp_find->key) == 1) {
				temp_find = temp_find->right_node;
			}
			else if (_comp.comparate(key, temp_find->key) == 2) {
				temp_find = temp_find->left_node;
			}
			else {
				break;
			}
		}
		if (temp_find == nullptr) {
			_way.push(nullptr);
			return nullptr;
		}

		return temp_find;
	}

	virtual void before_remove() {}

	virtual void after_remove(
		tkey key,
		std::stack<tree_node*> way
	) {}

	tvalue remove_node(tkey key, std::stack<tree_node*> _way) {
		tree_node* parent_node;
		if (_way.empty()) {
			tvalue temp_value = _root->value;
			_root->~tree_node();
			_root = nullptr;
			return temp_value;
		}
		tree_node* node = _way.top();

		if (node->left_node == nullptr and node->right_node == nullptr) {
			_way.pop();
			if (_way.empty()) {
				_root = nullptr;
			}
			else {
				parent_node = _way.top();
				if (_comp.comparate(key, parent_node->key) == 1) {
					parent_node->right_node = nullptr;
				}
				else {
					parent_node->left_node = nullptr;
				}
			}
			tvalue temp_value = node->value;
			node->~tree_node();
			node = nullptr;
			return temp_value;
		}
		else if (node->left_node == nullptr) {
			_way.pop();
			if (_way.empty()) {
				if (node->left_node != nullptr) {
					_root = node->left_node;
				}
				else {
					_root = node->right_node;
				}
			}
			else {
				parent_node = _way.top();
				if (parent_node->left_node == node) {
					parent_node->left_node = node->right_node;
				}
				else {
					parent_node->right_node = node->right_node;
				}
				/*tree_node* another = node->right_node;
				_way.push(node);
				while (another->left_node != nullptr) {
					_way.push(another);
					another = another->left_node;
				}*/
				/*tree_node* another_parent = _way.top();
				if (another_parent == node) {
					another_parent->right_node = nullptr;
					another_parent->left_node = another->left_node;
				}
				else {
					another_parent->left_node = nullptr;
					another_parent->right_node = another->right_node;
				}
				another->right_node = node->right_node;
				another->left_node = node->left_node;
				if (_comp.comparate(key, parent_node->key) == 1) {
					parent_node->right_node = another;
				}
				else {
					parent_node->left_node = another;
				}*/
			}
			tvalue temp_value = node->value;
			node->~tree_node();
			node = nullptr;
			return temp_value;
		}
		else if (node->right_node == nullptr) {
			_way.pop();
			if (_way.empty()) {
				if (node->left_node != nullptr) {
					_root = node->left_node;
				}
				else {
					_root = node->right_node;
				}
			}
			else {
				parent_node = _way.top();
				if (parent_node->left_node == node) {
					parent_node->left_node = node->left_node;
				}
				else {
					parent_node->right_node = node->left_node;
				}

			}
			tvalue temp_value = node->value;
			node->~tree_node();
			node = nullptr;
			return temp_value;
		}
		else {
			tree_node* another = node->right_node;
			_way.push(node);
			_way.push(another);
			while (another->left_node != nullptr) {
				_way.push(another);
				another = another->left_node;
			}
			node->value = another->value;
			node->key = another->key;
			_way.pop();
			tree_node* another_parrent = _way.top();
			if (another_parrent->left_node == another) {
				another_parrent->left_node = another->right_node;
			}
			else {
				another_parrent->right_node = another->right_node;
			}
			/*another->right_node = node->right_node;
			another->left_node = node->left_node;
			if (_comp.comparate(key, parent_node->key) == 1) {
				parent_node->right_node = another;
			}
			else {
				parent_node->left_node = another;
			}*/
			tvalue temp_value = node->value;
			another->~tree_node();
			another = nullptr;
			return temp_value;
		}
	}

public:

	tvalue find(tkey key) override {
		std::stack<tree_node*> _way;
		tree_node* node = findkey(key, _root, _way);
		if (node == nullptr) {
			throw std::invalid_argument("This key is not exist");
		}
		else {
			after_find(_way, node);
			return node->value;
		}

	}

	void insert(tkey key, tvalue& value) override {
		before_insert();
		std::stack<tree_node*> way;
		if (_root == nullptr) {
			_root = new tree_node;
			_root->value = value;
			_root->key = key;
			_root->left_node = nullptr;
			_root->right_node = nullptr;
			way.push(_root);
		}
		else {
			try {
				tree_node* temp = insert_key(key, value, way);
				inserted_after(way, temp);
			}
			catch (std::invalid_argument&) {
				throw std::invalid_argument("This key already exists");
			}
		}
		after_insert(way);
	}

	virtual tvalue remove(tkey key) override {
		before_remove();
		std::stack<tree_node*> _way;
		tree_node* node_remove = findkey(key, _root, _way);
		if (node_remove == nullptr) {
			throw std::invalid_argument("This key is node exist");
		}
		else {
			tvalue result = remove_node(key, _way);
			after_remove(key, _way);
			return result;
		}
	}

	virtual void before_right_rotate() {

	}

	virtual void after_right_rotate(
		tree_node* node,
		tree_node* new_node
	) {

	}

	tree_node** rotate_right(tree_node* node) {

		before_right_rotate();

		tree_node* temp = node->left_node;
		node->left_node = temp->right_node;
		temp->right_node = node;

		after_right_rotate(node, temp);

		return &temp;
	}

	virtual void before_left_rotate() {

	}

	virtual void after_left_rotate(
		tree_node* node,
		tree_node* new_node
	) {

	}

	tree_node** rotate_left(tree_node* node) {

		before_left_rotate();

		tree_node* temp = node->right_node;
		node->right_node = temp->left_node;
		temp->left_node = node;

		after_left_rotate(node, temp);

		return &temp;
	}

};

#endif	