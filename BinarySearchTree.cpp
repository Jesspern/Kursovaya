//#ifndef BINARYSEARCHTREE
//#define BINARYSEARCHTREE
//
//#include "associative_container.h"
//#include <stack>
//#include <stdexcept>
//#include "comparer.h"
//
//template<
//	typename tkey,
//	typename tvalue,
//	typename tkey_comparer>
//class binary_search_tree : public associative_container<tkey, tvalue, tkey_comparer>
//{
//private:
//
//	struct tree_node {
//		tkey key;
//		tvalue value;
//		tree_node* right_node;
//		tree_node* left_node;
//
//		virtual ~tree_node() noexcept = default;
//	};
//
//	tree_node* _root;
//	std::stack<tree_node*> _way;
//	tkey_comparer _comp;
//
//	virtual ~binary_search_tree() noexcept = default;
//
//public:
//
//	binary_search_tree() {
//		_root = nullptr;
//	}
//
//private:
//
//	void insert_key(tkey key, tvalue & value) {
//		tree_node* node_insert = findkey(key, _root);
//		if (node_insert == nullptr) {
//			node_insert = new tree_node;
//			node_insert->key = key;
//			node_insert->value = value;
//			tree_node* parent = _way.top();
//			if (_comp.compare(key, parent->key) == 1) {
//				parent->right_node = node_insert;
//			}
//			else {
//				parent->left_node = node_insert;
//			}
//		}
//		else {
//			throw std::invalid_argument("This key already exists");
//		}
//	}
//
//	tree_node* findkey(tkey key, tree_node* node) {
//		tree_node* temp_find = _root;
//		while (temp_find != nullptr) {
//			_way.push(temp_find);
//			if (_comp.compare(key, node->key) == 1) {
//				temp_find = temp_find->right_node;
//			}
//			else if (_comp.compare(key, node->key) == 2) {
//				temp_find = temp_find->left_node;
//			}
//			else {
//				break;
//			}
//		}
//		return temp_find;
//	}
//
//	tvalue remove_node(tkey key, tree_node* node) {
//		if (node->left_node == nullptr and node->right_node == nullptr) {
//			node->~tree_node();
//		}
//	}
//
//public:
//
//	tvalue find(tkey key) override {
//		tree_node* node = findkey(key, _root);
//		if (node == nullptr) {
//			throw std::invalid_argument("This key is not exist");
//		}
//		else {
//			return node->value;
//		}
//	}
//
//	void insert(tkey key, tvalue & value) override {
//		if (_root == nullptr) {
//			_root = new tree_node;
//			_root->value = value;
//			_root->key = key;
//			_root->left_node = nullptr;
//			_root->right_node = nullptr;
//		}
//		else {
//			try {
//				insert_key(key, value);
//			}
//			catch (std::invalid_argument& ) {
//				throw std::invalid_argument("This key already exists");
//			}
//		}
//	}
//
//	tvalue remove(tkey key) override {
//		tree_node* node_remove = findkey(key, _root);
//		if (node_remove == nullptr) {
//			throw std::invalid_argument("This key is node exist");
//		}
//		else {
//			remove_node(key, node_remove);
//		}
//	}
//
//};
//
//#endif BINARYSEARCHTREE	