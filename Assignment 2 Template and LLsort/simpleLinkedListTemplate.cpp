#pragma once

#ifndef SIMPLELINKEDLISTTEMPLATEHPP
#define SIMPLELINKEDLISTTEMPLATEHPP

#include <iostream>
#include "simpleLinkedListTemplate.h"
using namespace std;


template <class T>
ListNode<T>::ListNode(T n)
{
	_item = n;
	_next = NULL;
}

template <class T>
void List<T>::insertHead(T n)
{
	ListNode<T> *aNewNode = new ListNode<T>(n);
	aNewNode->_next = _head;
	_head = aNewNode;
	_size++;
};

template <class T>
void List<T>::removeHead()
{
	if (_size > 0) {
		ListNode<T> *temp = _head;
		_head = _head->_next;
		delete temp;
		_size--;
	}
}

template <class T>
void List<T>::print(bool withNL) {

	ListNode<T> *temp = _head;
	while (temp) {
		cout << temp->_item;
		if (withNL)
			cout << endl;
		else
			cout << " ";
		temp = temp->_next;
	}
	cout << endl;
	  
}

template <class T>
bool List<T>::exist(T n) {

	// modify this
	return false; 
}

template <class T>
T List<T>::headItem()
{
	if (_size)
		return *_head;
}

template <class T>
T List<T>::extractMax()
{
	ListNode<T>* maxNode = _head;
	ListNode<T>* prevNode = NULL;
	ListNode<T>* tempNode = _head;

	T maxItem = _head->_item;

	while (tempNode != NULL) {
		if (tempNode->_item > maxItem) {
			maxItem = tempNode->_item;   //updates maxItem with the new max value
			maxNode = tempNode;          //and maxNode with the current node
		}
		tempNode = tempNode->_next;      //moves tempNode to the next node
	}

	T extMax = maxNode->_item;


	if (maxNode != _head) {
		prevNode = _head;
		while (prevNode->_next != maxNode) {
			prevNode = prevNode->_next;
		}
		prevNode->_next = maxNode->_next;
		delete maxNode;
		_size--;
	}
	else {
		removeHead();
	}
	return extMax;
}
template <class T>
T List<T>::searchMin() {
	ListNode<T>* curr = _head;
	T minimum = _head->_item;

	while (curr != NULL) {
		if (curr->_item < minimum) {
			minimum = curr->_item;
		}
		curr = curr->_next;
	}
	return minimum;
}

template <class T>
void List<T>::reverseOp() {
	ListNode<T>* prev = NULL;
	ListNode<T>* current = _head;
	ListNode<T>* next = NULL;

	while (current != NULL) {
		next = current->_next;
		current->_next = prev;
		prev = current;
		current = next;
	}
	_head = prev; // Set the new head of the list

}



template <class T>
List<T>::~List()
{
	while (_head)
		removeHead();
};


#endif