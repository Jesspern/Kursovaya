#ifndef AVLTREE
#define AVLTREE

#include "associative_container.h"
#include "BinarySearchTree.cpp"
#include "comparer.h"
#include <stdlib.h>
#include <stdio.h>

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
class avltree final : public binary_search_tree<tkey, tvalue, tkey_comparer> {

	using bst = binary_search_tree<tkey, tvalue, tkey_comparer>;

public:

	avltree() {
		bst::_root = nullptr;
	}

	~avltree() noexcept = default;

	struct avl_node : public bst::tree_node {
		long height;
	};

	avl_node* to_avl(typename bst::tree_node* node) {
		return reinterpret_cast<avl_node*>(node);
	}

	long get_height_difference(typename bst::tree_node* node) {
		return get_height(node->left_node) - get_height(node->right_node);
	}

	long get_height(typename bst::tree_node* node) {
		if (node) {
			return to_avl(node)->height;
		}
		else {
			return 0;
		}
	}

	void set_height_node(typename bst::tree_node* node) {
		long left_child = get_height(node->left_node);
		long right_child = get_height(node->right_node);
		to_avl(node)->height = std::max(left_child, right_child) + 1;
	}

	void after_right_rotate(
		typename bst::tree_node* node,
		typename bst::tree_node* new_node
	) {
		set_height_node(node);
		set_height_node(new_node);
	}

	void after_left_rotate(
		typename bst::tree_node* node,
		typename bst::tree_node* new_node
	) {
		set_height_node(node);
		set_height_node(new_node);
	}

	typename bst::tree_node** balance_node(typename bst::tree_node* node) {
		if (get_height_difference(node) == -2) {
			if (get_height_difference(node->right_node) > 0) {
				node->right_node = *(bst::rotate_right(node->right_node));
			}
			return bst::rotate_left(node);
		}
		if (get_height_difference(node) == 2) {
			if (get_height_difference(node->left_node) < 0) {
				node->left_node = *(bst::rotate_left(node->left_node));
			}
			return bst::rotate_right(node);
		}
		return &node;
	}

	void balance_tree(std::stack<typename bst::tree_node*> way) {
		while (!(way.empty())) {
			typename bst::tree_node* current_node = way.top();
			way.pop();
			set_height_node(current_node);

			typename bst::tree_node* temp_root = *(balance_node(current_node));

			if (!(way.empty())) {
				typename bst::tree_node* parent = way.top();
				if (parent->left_node == current_node) {
					parent->left_node = temp_root;
				}
				else if (parent->right_node == current_node) {
					parent->right_node = temp_root;
				}
			}
			else {
				bst::_root = temp_root;
			}
		}
	}

	void after_insert(std::stack<typename bst::tree_node*> way) override {
		balance_tree(way);
	}

	void after_remove(
		tkey key,
		std::stack<typename bst::tree_node*> way
	) override {
		balance_tree(way);
	}

};

#endif