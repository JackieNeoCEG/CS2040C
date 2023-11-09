#include <iostream>
#include "simpleIntLinkedList.h"
using namespace std;

ListNode::ListNode(int n)
{
	_item = n;
	_next = NULL;
}

void List::insertHead(int n)
{
	ListNode *aNewNode = new ListNode(n);
	aNewNode->_next = _head;
	_head = aNewNode;
	_size++;
};

void List::removeHead()
{
	if (_size > 0) {
		ListNode *temp = _head;
		_head = _head->_next;
		delete temp;
		_size--;
	}
}

void List::print() {
	ListNode* ptr = _head;
	while (ptr) {
		cout << ptr->_item << " "; //a separator that will be printed between one node and the next
		ptr = ptr->_next;
	}
	cout << endl;
}

bool List::exist(int n) {
	int counter = 0;
	ListNode* ptr = _head;
	while (ptr != NULL) {
		if (ptr->_item == n) {
			counter++;
		}
		ptr = ptr->_next;
	}
	return counter;
}

int List::headItem()
{
	if (_size) {
		return _head->_item;
	}
}

List::~List()
{
	while (_size != 0)
		removeHead();
};

