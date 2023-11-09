#pragma once
#include <iostream>
using namespace std;

template <class T>
class BinarySearchTree;

template <class T>
class TreeNode {
private:
	T _item;
	TreeNode<T>* _left;
	TreeNode<T>* _right;
	int _height;
	int _weight; // new addition
public:
	TreeNode(T x) { _left = _right = NULL; _item = x; _height = 0; _weight = 1; };

	friend BinarySearchTree<T>;
};

template <class T>
class BinarySearchTree {
protected:
	int _size;
	TreeNode<T>* _root;
	void _printTree(int indent, TreeNode<T>*, bool withHeightAndWeight);

	// The following functions are optional for you to implement. 
	TreeNode<T>*  _insert(TreeNode<T>* current, T x);
	void _inOrderPrint(TreeNode<T>*);
	void _postOrderPrint(TreeNode<T>*);
	void _preOrderPrint(TreeNode<T>*);
	TreeNode<T>* _rightRotation(TreeNode<T>*);
	TreeNode<T>* _leftRotation(TreeNode<T>*);
	TreeNode<T>* _searchMax(TreeNode<T>*);
	TreeNode<T>* _searchMin(TreeNode<T>*);
	TreeNode<T>* _search(TreeNode<T>*, T);
	void _destroySubTree(TreeNode<T>*);
	void _updateW(TreeNode<T>*);
	int _rank(TreeNode<T>* , const T& x);
	T _select(TreeNode<T>*,int rank);


public:
	BinarySearchTree() { _root = NULL; _size = 0; }
	~BinarySearchTree();
	int size() { return _size; };
	void insert(T);
	void printTree(bool withHeightAndWeight = 1);
	void inOrderPrint();
	void postOrderPrint();
	void preOrderPrint();
	T searchMax() { return T(); }; 
	T searchMin() { return T(); };
	bool exist(T x) { return T(); };
	T search(T x) { return T(); };
	T successor(T);

	int rank(const T& x);
	T select(int rank);

};


template <class T>
void BinarySearchTree<T>::_updateW(TreeNode<T>* node) {
	if (node == nullptr) {
		return;
	}

	// Recursively update weight of left and right subtrees
	_updateW(node->_left);
	_updateW(node->_right);

	// Update weight of current node
	node->_weight = 1; // Initialize to 1 (counting the current node)

	if (node->_left) {
		node->_weight += node->_left->_weight;
	}
	if (node->_right) {
		node->_weight += node->_right->_weight;

	}
}

template <class T>
void BinarySearchTree<T>::insert(T x)
{
	_root = _root ? _insert(_root, x) : new TreeNode<T>(x);
	if (_size == 0) _size++;
	_updateW(_root);
}

template <class T>
void BinarySearchTree<T>::_printTree(int indent, TreeNode<T>* node, bool withHeightAndWeight) {

	if (!node)
		return;

	if (node->_right)
		_printTree(indent + 2, node->_right, withHeightAndWeight);
	for (int i = 0; i < indent; i++)
		cout << "  ";
	cout << node->_item;
	if (withHeightAndWeight)
		cout << "(h=" << node->_height << ",w=" << node->_weight << ")";
	cout << endl;
	if (node->_left)
		_printTree(indent + 2, node->_left, withHeightAndWeight);


};

template <class T>
void BinarySearchTree<T>::printTree(bool withHeightAndWeight) {
	_printTree(0, _root, withHeightAndWeight);
}


template <class T>
void BinarySearchTree<T>::preOrderPrint() {

	_preOrderPrint(_root);
	cout << endl;
}


template <class T>
void BinarySearchTree<T>::_preOrderPrint(TreeNode<T>* node) {
	if (!node) return;
	cout << node->_item << " ";
	_preOrderPrint(node->_left);
	_preOrderPrint(node->_right);
}


template <class T>
void BinarySearchTree<T> ::_destroySubTree(TreeNode<T>* node)
{
	if (node->_left)
		_destroySubTree(node->_left);
	if (node->_right)
		_destroySubTree(node->_right);
	delete node;
}

template <class T>
BinarySearchTree<T> :: ~BinarySearchTree()
{
	if (_root)
		_destroySubTree(_root);
}


template <class T>
void BinarySearchTree<T>::inOrderPrint() {
}


template <class T>
void BinarySearchTree<T>::_inOrderPrint(TreeNode<T>* node) {
}


template <class T>
void BinarySearchTree<T>::postOrderPrint() {
}


template <class T>
void BinarySearchTree<T>::_postOrderPrint(TreeNode<T>* node) {
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_insert(TreeNode<T>* current, T x) {


	if (current->_item > x)
	{
		if (current->_left)
			current->_left = _insert(current->_left, x);
		else
		{
			current->_left = new TreeNode<T>(x);
			_size++;
		}
	}
	else if (x > current->_item) {
		if (current->_right)
			current->_right = _insert(current->_right, x);
		else
		{
			current->_right = new TreeNode<T>(x);
			_size++;
		}
	}
	else {
		return current; // When the node already existed in the tree
	}

	int leftHeight = current->_left ? current->_left->_height : -1;
	int rightHeight = current->_right ? current->_right->_height : -1;
	current->_height = 1 + max(leftHeight, rightHeight);
	current->_weight = 1 + (current->_left ? current->_left->_weight : 0) + (current->_right ? current->_right->_weight : 0);

	int balance = leftHeight - rightHeight;
	if (balance > 1) { //left-heavy
		if (x > current->_left->_item) { //left side is right heavy
			current->_left = _leftRotation(current->_left);
		}
		return _rightRotation(current);
	}
	else if (balance < -1) { //right-heavy
		if (x < current->_right->_item) {
			current->_right = _rightRotation(current->_right); //right side is left heavy
		}
		return _leftRotation(current);
	}
	return current;

}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_searchMax(TreeNode<T>* current) {
	return current;
}


template <class T>
TreeNode<T>* BinarySearchTree<T>::_searchMin(TreeNode<T>* current) {
	return current;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_search(TreeNode<T>* current, T x) {
	if (current == NULL || current->_item == x) {
		return current;
	}
	if (x < current->_item) {
		return _search(current->_left, x);
	}
	return _search(current->_right, x);

}


template <class T>
T BinarySearchTree<T>::successor(T x)
{
	return T();
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_leftRotation(TreeNode<T>* A)
{
	TreeNode<T>* B = A->_right;
	if (B == nullptr) {
		return A; // Cannot perform left rotation if right child is null
	}
	A->_right = B->_left;
	B->_left = A;
	A->_height = 1 + max(A->_left ? A->_left->_height : -1, A->_right ? A->_right->_height : -1);
	B->_height = 1 + max(B->_left ? B->_left->_height : -1, B->_right ? B->_right->_height : -1);

	return B;

}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_rightRotation(TreeNode<T>* A)
{
	TreeNode<T>* B = A->_left;
	if (B == nullptr) {
		return A; // Cannot perform left rotation if right child is null
	}
	A->_left = B->_right;
	B->_right = A;
	A->_height = 1 + max(A->_left ? A->_left->_height : -1, A->_right ? A->_right->_height : -1);
	B->_height = 1 + max(B->_left ? B->_left->_height : -1, B->_right ? B->_right->_height : -1);
	return B;
}

template <class T>
int BinarySearchTree<T>::rank(const T& x) {
	return _rank(_root, x);
}

template <class T>
int BinarySearchTree<T>::_rank(TreeNode<T>* node, const T& x) {
	TreeNode<T>* check = _search(node, x);
	if (check == NULL) {
		return -1;
	}

	if (x == node->_item) {
		return (node->_left ? node->_left->_weight : 0) + 1;
	}

	if (x < node->_item) {
		return _rank(node->_left, x);
	}
	else {
		return _rank(node->_right, x) + (node->_left ? node->_left->_weight : 0) + 1;
	}
}

template <class T>
T  BinarySearchTree<T>::select(int rank)
{
	return _select(_root, rank);
}

template <class T>
T BinarySearchTree<T>::_select(TreeNode<T>* current, int rank) {
	int currentRank = 1 + (current->_left ? current->_left->_weight : 0);

	if (rank == currentRank) {
		return current->_item;
	}
	else if (rank < currentRank) {
		return _select(current->_left, rank);
	}
	else {
		return _select(current->_right, rank - currentRank);
	}
}
