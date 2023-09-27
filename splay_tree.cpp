#include <iostream>
#include <stack>
#include "Comparer.cpp"
#include <stdexcept>

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
class splay_tree final
{

protected:

	struct node
	{

		tkey key;
		tvalue value;
		node* left_subtree;
		node* right_subtree;

	};

private:

	node* _tree_root;
	std::stack <splay_tree<tkey, tvalue, tkey_comparer>::node*> way;
	tkey_comparer _comp;

public:

	splay_tree();
	
	splay_tree(tkey _key, tvalue _value);

	~splay_tree() {};

public:

	node** zig_right(node* root);

	node** zig_left(node* root);

	node** zigzig_right(node* root);

	node** zigzig_left(node* root);

	node** zigzag_leftright(node* root);

	node** zigzag_rightleft(node* root);

	void splay(node* el);

public:

	node* find(tkey search);

	node* down(tkey search, node* root);

	void insert(tkey id, tvalue inter);

	node* remove(tkey id);

	node* merge(node* tree_root1, node* tree_root2);

	void set_root(tvalue mean);

	void print_root();

	void change_node(tkey search, tvalue mean);
};

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer>::splay_tree()
{
	_tree_root = nullptr;
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer>::splay_tree(tkey _key, tvalue _value)
{
	_tree_root = new splay_tree<tkey, tvalue, tkey_comparer>::node;
	_tree_root->key = _key;
	_tree_root->value = _value;
	_tree_root->left_subtree = nullptr;
	_tree_root->right_subtree = nullptr;
}

template<
	typename tkey, 
	typename tvalue, 
	typename tkey_comparer>
typename splay_tree<tkey, tvalue, tkey_comparer>::node** splay_tree<tkey, tvalue, tkey_comparer>::zig_right
	(splay_tree<tkey, tvalue, tkey_comparer>::node* root)
{
	splay_tree<tkey, tvalue, tkey_comparer>::node* temp = root->left_subtree;
	root->left_subtree = temp->right_subtree;
	temp->right_subtree = root;
	return &temp;
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename splay_tree<tkey, tvalue, tkey_comparer>::node** splay_tree<tkey, tvalue, tkey_comparer>::zig_left(splay_tree<tkey, tvalue, tkey_comparer>::node* root)
{
	splay_tree<tkey, tvalue, tkey_comparer>::node* temp = root->right_subtree;
	root->right_subtree = temp->left_subtree;
	temp->left_subtree = root;
	return &temp;
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename splay_tree<tkey, tvalue, tkey_comparer>::node** splay_tree<tkey, tvalue, tkey_comparer>::zigzig_right(splay_tree<tkey, tvalue, tkey_comparer>::node* root)
{
	return (zig_right(*(zig_right(root))));
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename splay_tree<tkey, tvalue, tkey_comparer>::node** splay_tree<tkey, tvalue, tkey_comparer>::zigzig_left(splay_tree<tkey, tvalue, tkey_comparer>::node* root)
{
	return (zig_left(*(zig_left(root))));
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename splay_tree<tkey, tvalue, tkey_comparer>::node** splay_tree<tkey, tvalue, tkey_comparer>::zigzag_leftright(splay_tree<tkey, tvalue, tkey_comparer>::node* root)
{
	root->left_subtree = *(zig_left(root->left_subtree));
	return zig_right(root);
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename splay_tree<tkey, tvalue, tkey_comparer>::node** splay_tree<tkey, tvalue, tkey_comparer>::zigzag_rightleft(splay_tree<tkey, tvalue, tkey_comparer>::node* root)
{
	root->right_subtree = *(zig_right(root->right_subtree));
	return zig_left(root);
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void splay_tree<tkey, tvalue, tkey_comparer>::splay(splay_tree<tkey, tvalue, tkey_comparer>::node* el)
{
	while (way.size() != 0) {
		if (way.size() == 1) {
			splay_tree<tkey, tvalue, tkey_comparer>::node* parent_1 = way.top();
			way.pop();
			if (parent_1->right_subtree == el) {
				_tree_root = *(zig_left(parent_1));
			}
			else if (parent_1->left_subtree == el) {
				_tree_root = *(zig_right(parent_1));
			}
		}
		else {
			splay_tree<tkey, tvalue, tkey_comparer>::node* parent_1 = way.top();
			way.pop();
			splay_tree<tkey, tvalue, tkey_comparer>::node* parent_2 = way.top();
			way.pop();
			if (parent_1->left_subtree == el) {
				if (parent_2->left_subtree == parent_1) {
					el = *(zigzig_right(parent_2));
					if (way.size() != 0)
						way.top()->left_subtree = el;
				}
				else if (parent_2->right_subtree == parent_2) {
					el = *(zigzag_rightleft(parent_2));
					if (way.size() != 0)
						way.top()->right_subtree = el;
				}
			}
			else if (parent_1->right_subtree == el) {
				if (parent_2->left_subtree == parent_1) {
					el = *(zigzag_leftright(parent_2));
					if (way.size() != 0)
						way.top()->left_subtree = el;
				}
				else if (parent_2->right_subtree == parent_1) {
					el = *(zigzig_left(parent_2));
					if (way.size() != 0)
						way.top()->right_subtree = el;
				}
			}
			if (way.size() == 0) {
				_tree_root = el;
				continue;
			}
		}
	}
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename splay_tree<tkey, tvalue, tkey_comparer>::node* splay_tree<tkey, tvalue, tkey_comparer>::find(tkey search)
{
	splay_tree<tkey, tvalue, tkey_comparer>::node* temp = down(search, _tree_root);
	if (temp->key != search) {
		throw std::invalid_argument("ID is not correct");
	}
	else {
		way.pop();
		splay(temp);

		return _tree_root;
	}
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename splay_tree<tkey, tvalue, tkey_comparer>::node* splay_tree<tkey, tvalue, tkey_comparer>::down(tkey search, splay_tree<tkey, tvalue, tkey_comparer>::node* root)
{
	if (_comp.comparate(search, root->key) == 2 and root->left_subtree != nullptr) {
		way.push(root);
		return down(search, root->left_subtree);
	}
	else if (_comp.comparate(search, root->key) == 1 and root->right_subtree != nullptr) {
		way.push(root);
		return down(search, root->right_subtree);
	}
	else {
		way.push(root);
		return root;
	}
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void splay_tree<tkey, tvalue, tkey_comparer>::insert(tkey id, tvalue inter)
{
	if (_tree_root == nullptr) {
		splay_tree<tkey, tvalue, tkey_comparer>::node* ins = new splay_tree<tkey, tvalue, tkey_comparer>::node;
		ins->key = id;
		ins->value = inter;
		ins->left_subtree = nullptr;
		ins->right_subtree = nullptr;
		_tree_root = ins;
	}
	else {
		splay_tree<tkey, tvalue, tkey_comparer>::node* temp = down(id, _tree_root);
		splay_tree<tkey, tvalue, tkey_comparer>::node* ins = new splay_tree<tkey, tvalue, tkey_comparer>::node;
		ins->key = id;
		ins->value = inter;
		ins->left_subtree = nullptr;
		ins->right_subtree = nullptr;
		if (_comp.comparate(id, temp->key) == 0) {
			std::cout << "Mistake with element";
		}
		else if (_comp.comparate(id, temp->key) == 2) {
			temp->left_subtree = ins;
		}
		else
			temp->right_subtree = ins;
		splay(ins);
	}
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename splay_tree<tkey, tvalue, tkey_comparer>::node* splay_tree<tkey, tvalue, tkey_comparer>::remove(tkey search)
{	
	splay_tree<tkey, tvalue, tkey_comparer>::node* temp = down(search, _tree_root);
	if (_comp.comparate(temp->key, search) != 0) {
		std::cout << "Mistake with remove element";
		return temp;
	}
	else {
		way.pop();
		splay(temp);
		_tree_root = merge(temp->left_subtree, temp->right_subtree);
		delete temp;
	}
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename splay_tree<tkey, tvalue, tkey_comparer>::node* splay_tree<tkey, tvalue, tkey_comparer>::merge(splay_tree<tkey, tvalue, tkey_comparer>::node* tree1_root, splay_tree<tkey, tvalue, tkey_comparer>::node* tree2_root)
{
	splay_tree<tkey, tvalue, tkey_comparer>::node* temp = tree1_root;
	while (temp->right_subtree != nullptr) {
		way.push(temp);
		temp = temp->right_subtree;
	}
	splay(temp);
	temp->right_subtree = tree2_root;
	return temp;

}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void splay_tree<tkey, tvalue, tkey_comparer>::set_root(tvalue mean)
{
	_tree_root->value = mean;
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void splay_tree<tkey, tvalue, tkey_comparer>::print_root()
{
	std::cout << "Id -> " << _tree_root->key << ", Value -> " << _tree_root->value << std::endl;
}

template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void splay_tree<tkey, tvalue, tkey_comparer>::change_node(tkey search, tvalue mean)
{
	down(search, _tree_root)->value = mean;
	way.size() = 0;
}


/*int main()
{
	binary_search_tree<int, int, int> test(10, 20);

	test.print_root();

	test.insert(15, 16);

	test.insert(5, 5);
	
	test.insert(20, 21);

	test.print_root();

	std::cout << "Search: " << (test.find(15))->value << std::endl;

	test.remove(15);

	test.print_root();

	test.change_node(20, 18);

	//std::cout << "Id -> " << test._tree_root->key << ", Value -> " << test._tree_root->value << std::endl;

	return 0;
}*/