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
	TreeNode<T>* _parent; //new pointer
	int _height;
public:
	TreeNode(T x) { _left = _right = _parent = NULL; _item = x; _height = 0; };

	friend BinarySearchTree<T>;
};

template <class T>
class BinarySearchTree {
protected:
	int _size;
	TreeNode<T>* _root;
	void _printTree(int indent, TreeNode<T>*, bool withHeight);

	//The following functions are optional for you to implement.
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
	

public:
	BinarySearchTree() { _root = NULL; _size = 0; }
	~BinarySearchTree();
	int size() { return _size; };
	void insert(T);
	void printTree(bool withHeight = 1);
	void inOrderPrint();
	void postOrderPrint();
	void preOrderPrint();
	T searchMax(); 
	T searchMin();
	bool exist(T x);
	T successor(T);

};

template <class T>
bool BinarySearchTree<T>::exist(T x) {
    TreeNode<T>* curr = _root;
	while (curr != NULL) {
		if (curr->_item == x) {
			return true;
		}
		else if (x < curr->_item) {
			curr = curr->_left;  // Traverse to the left subtree
		}
		else {
			curr = curr->_right;
		}
	}
	return false;
}

template <class T>
void BinarySearchTree<T>::insert(T x) {
	_root = _root ? _insert(_root, x) : new TreeNode<T>(x);
	if (_size == 0) _size++; 
}

template <class T>
void BinarySearchTree<T>::_printTree(int indent, TreeNode<T>* node, bool withHeight) {

	if (!node)
		return;

	if (node->_right)
		_printTree(indent + 2, node->_right, withHeight);
	for (int i = 0; i < indent; i++) {
		cout << "  ";
	}
	cout << node->_item;
	if (withHeight)
		cout << "(h=" << node->_height << ")";
	cout << endl;
	if (node->_left)
		_printTree(indent + 2, node->_left, withHeight);

	
};

template <class T>
void BinarySearchTree<T>::printTree(bool withHeight) {
	_printTree(0, _root, withHeight);
}

template <class T> void BinarySearchTree<T>::preOrderPrint() {
	_preOrderPrint(_root);
	cout << "\n";
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
	_inOrderPrint(_root);
	cout << "\n";
}

template <class T>
void BinarySearchTree<T>::_inOrderPrint(TreeNode<T> *node) {
	if (!node) return;

	_inOrderPrint(node->_left);
	cout << node->_item << " ";
	_inOrderPrint(node->_right);
}


template <class T>
void BinarySearchTree<T>::postOrderPrint() {
	_postOrderPrint(_root);
	cout << "\n";
}

template <class T>
void BinarySearchTree<T>::_postOrderPrint(TreeNode<T> *node) {
	if (!node) return;

	_postOrderPrint(node->_left);
	_postOrderPrint(node->_right);
	cout << node->_item << " ";
}




template <class T>
TreeNode<T>* BinarySearchTree<T>::_insert(TreeNode<T>* current, T x) {
	if (current->_item > x)
	{
		if (current->_left) {
			current->_left = _insert(current->_left, x);
			current->_left->_parent = current;
		}
		else
		{
			current->_left = new TreeNode<T>(x);
			current->_parent = NULL;
			_size++;
			
		}
	}
	else if (x > current->_item) {
		if (current->_right) {
			current->_right = _insert(current->_right, x);
			current->_right->_parent = current;
		}
		else
		{
			current->_right = new TreeNode<T>(x);
			current->_parent = NULL;
			_size++;

		}
	}
	else
	return current; // When the node already existed in the tree

	int leftHeight = current->_left ? current->_left->_height : -1;
	int rightHeight = current->_right ? current->_right->_height : -1;
	current->_height = 1 + max(leftHeight, rightHeight);
	
	int balance = leftHeight - rightHeight;

	if (balance > 1) {
		if (x < current->_left->_item) {
			// Left-Left case, perform right rotation
			return _rightRotation(current);
		}
			// Left-Right case, perform left-right rotation
		current->_left = _leftRotation(current->_left);
		return _rightRotation(current);
	}
	else if (balance < -1) {
		if (x > current->_right->_item) {
			// Right-Right case, perform left rotation
			return _leftRotation(current);
		}
			// Right-Left case, perform right-left rotation
		current->_right = _rightRotation(current->_right);
	  	return _leftRotation(current);

	}
	return current;

}



template <class T>
TreeNode<T>* BinarySearchTree<T>::_searchMax(TreeNode<T>* current) {
	while (current != NULL && current->_right != NULL) {
		current = current->_right;
	}
	return current;
}

template <class T>
T BinarySearchTree<T>::searchMax() {
	TreeNode<T>* maxNode = _searchMax(_root);
	return maxNode->_item;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_searchMin(TreeNode<T>* current) {
	while (current != NULL && current->_left != NULL) {
		current = current->_left;
	}
	return current;
}

template <class T>
T BinarySearchTree<T>::searchMin() {
	TreeNode<T>* minNode = _searchMin(_root);
	return minNode->_item;
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
T BinarySearchTree<T>::successor(T x) {	
	TreeNode<T>* node = _search(_root, x);

	if (node == NULL) { //search unsuccessful so estimate closest case
		node = _root; // Start from the root
		TreeNode<T>* closest = NULL;
		while (node != NULL) {
			if (x < node->_item) {
				closest = node;
				node = node->_left;
			}
			else if (x > node->_item) {
				node = node->_right;
			}
		}

		if (closest == NULL) {
			return T(); //tree empty
		}
		return closest->_item; // Return the closest value found

	}

	if (node->_right != NULL) {
		 TreeNode<T>* curr = node->_right; //goes to right subtree
		 while (curr->_left != NULL) //successor is leftmost node in right subtree
			  	curr = curr->_left;
		 return curr->_item;
	}

	TreeNode<T>* parent = node->_parent; //no right subtree
	while (parent != NULL && node == parent->_right) {
		node = parent;
		parent = parent->_parent;
	}
	if (parent == NULL) {
		return T();
	}
	return parent->_item;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_leftRotation(TreeNode<T>* node)
{
	TreeNode<T>* newRoot = node->_right;
	node->_right = newRoot->_left;
	if (newRoot->_left) {
		newRoot->_left->_parent = node; // Updates parent pointer of left child
	}

	newRoot->_left = node;
	newRoot->_parent = node->_parent;
	node->_parent = newRoot;

	if (newRoot->_parent) {
		if (node == newRoot->_parent->_left) {
			newRoot->_parent->_left = newRoot;
		}
		else {
			newRoot->_parent->_right = newRoot;
		}
	}
	int leftHeight = node->_left ? node->_left->_height : -1;
	int rightHeight = node->_right ? node->_right->_height : -1;
	node->_height = 1 + max(leftHeight, rightHeight);

	leftHeight = newRoot->_left ? newRoot->_left->_height : -1;
	rightHeight = newRoot->_right ? newRoot->_right->_height : -1;
	newRoot->_height = 1 + max(leftHeight, rightHeight); 
	return newRoot;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_rightRotation(TreeNode<T>* node)
{
	TreeNode<T>* newRoot = node->_left;
	node->_left = newRoot->_right;
	if (newRoot->_right) {
		newRoot->_right->_parent = node; // Updates parent pointer of right child
	}

	newRoot->_right = node;
	newRoot->_parent = node->_parent;
	node->_parent = newRoot;

	if (newRoot->_parent) {
		if (node == newRoot->_parent->_left) {
			newRoot->_parent->_left = newRoot;
		}
		else {
			newRoot->_parent->_right = newRoot;
		}
	}


	int leftHeight = node->_left ? node->_left->_height : -1;
	int rightHeight = node->_right ? node->_right->_height : -1;
	node->_height = 1 + max(leftHeight, rightHeight);

	leftHeight = newRoot->_left ? newRoot->_left->_height : -1;
	rightHeight = newRoot->_right ? newRoot->_right->_height : -1;
	newRoot->_height = 1 + max(leftHeight, rightHeight);
	return newRoot;
}
