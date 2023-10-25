#ifndef SPLAYTREE
#define SPLAYTREE

#include "associative_container.h"
#include "comparer.h"
#include "BinarySearchTree.cpp"

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
class splay_tree final : public binary_search_tree<tkey, tvalue, tkey_comparer> {

	using bst = binary_search_tree<tkey, tvalue, tkey_comparer>;

public:

	splay_tree() {
		bst::_root = nullptr;
	}

	~splay_tree() noexcept = default;

private:

	typename bst::tree_node** zigzig_right(typename bst::tree_node* root) {
		return (bst::rotate_right(*(bst::rotate_right(root))));
	}

	typename bst::tree_node** zigzig_left(typename bst::tree_node* root) {
		return (bst::rotate_left(*(bst::rotate_left(root))));
	}

	typename bst::tree_node** zigzag_leftright(typename bst::tree_node* root) {
		root->left_node = *(bst::rotate_left(root->left_node));
		return bst::rotate_right(root);
	}

	typename bst::tree_node** zigzag_rightleft(typename bst::tree_node* root) {
		root->right_node = *(bst::rotate_right(root->right_node));
		return bst::rotate_left(root);
	}

	void splay(std::stack<typename bst::tree_node*> way, typename bst::tree_node* el) {
		way.pop();
		while (way.size() != 0) {
			if (way.size() == 1) {
				typename bst::tree_node* parent_1 = way.top();
				way.pop();
				if (parent_1->right_node == el) {
					bst::_root = *(bst::rotate_left(parent_1));
				}
				else if (parent_1->left_node == el) {
					bst::_root = *(bst::rotate_right(parent_1));
				}
				break;
			}
			typename bst::tree_node* parent_1 = way.top();
			way.pop();
			typename bst::tree_node* parent_2 = way.top();
			way.pop();
			if (parent_1->left_node == el) {
				if (parent_2->left_node == parent_1) {
					el = *(zigzig_right(parent_2));
					if (way.size() != 0)
						way.top()->left_node = el;
				}
				else if (parent_2->right_node == parent_2) {
					el = *(zigzag_rightleft(parent_2));
					if (way.size() != 0)
						way.top()->right_node = el;
				}
			}
			else if (parent_1->right_node == el) {
				if (parent_2->left_node == parent_1) {
					el = *(zigzag_leftright(parent_2));
					if (way.size() != 0)
						way.top()->left_node = el;
				}
				else if (parent_2->right_node == parent_1) {
					el = *(zigzig_left(parent_2));
					if (way.size() != 0)
						way.top()->right_node = el;
				}
			}
			if (way.size() == 0) {
				bst::_root = el;
				continue;
			}
		}
	}

public:

	void after_insert(
		std::stack<typename bst::tree_node*> way
	) override {
		splay(way, way.top());
	}

	void after_find(
		std::stack<typename bst::tree_node*> way,
		typename bst::tree_node* node
	) override {
		splay(way, node);
	}

	void inserted_after(
		std::stack<typename bst::tree_node*> way,
		typename bst::tree_node* node
	) override {
		splay(way, node);
	}

	void merge(typename bst::tree_node* tree1_root, typename bst::tree_node* tree2_root) {
		typename bst::tree_node* temp = tree1_root;
		std::stack<typename bst::tree_node*> way;
		while (temp->right_node != nullptr) {
			way.push(temp);
			temp = temp->right_node;
		}
		way.push(temp);
		splay(way, temp);
		temp->right_node = tree2_root;
		this->_root = temp;
	}

	typename bst::tree_node* down(tkey search, bst::tree_node* root, std::stack<typename bst::tree_node*>& way) {
		if (typename bst::_comp.comparate(search, root->key) == 2 and root->left_node != nullptr) {
			way.push(root);
			return down(search, root->left_node, way);
		}
		else if (typename bst::_comp.comparate(search, root->key) == 1 and root->right_node != nullptr) {
			way.push(root);
			return down(search, root->right_node, way);
		}
		else {
			way.push(root);
			return root;
		}
	}

	tvalue remove(tkey key) {
		std::stack<typename bst::tree_node*> way;
		typename bst::tree_node* temp = down(key, bst::_root, way);
		if (typename bst::_comp.comparate(temp->key, key) != 0) {
			std::cout << "Mistake with remove element" << std::endl;
			return temp->value;
		}
		else {
			splay(way, temp);
			merge(temp->left_node, temp->right_node);
			tvalue value = temp->value;
			delete temp;
			return value;
		}
	}

	void print_root() {
		std::cout << bst::_root->value << std::endl;
	}

};

#endif