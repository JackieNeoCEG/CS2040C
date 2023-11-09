#pragma once
#include <math.h>

#include <iostream>
using namespace std;

#ifndef HEAPHPP
#define HEAPHPP

template <class T>
void Heap<T>::_bubbleUp(int index) {
	int parent = floor((index - 1) / 2);
	while (index > 0 && (_heap[index] >_heap[parent])) { //root excluded
		swap(_heap[index], _heap[parent]);
		index = parent;
		parent = floor((index - 1) / 2);
	}
}

template <class T>
void Heap<T>::_bubbleDown(int index) {
	int leftChild = 2 * index + 1;
	int rightChild = 2 * index + 2;
	int temp = index;

	if (_n > leftChild && (_heap[leftChild] > _heap[temp])) {
		temp = leftChild;
	}
	if (_n > rightChild && (_heap[rightChild] > _heap[temp])) {
		temp = rightChild;
	}

	if (temp != index) { //bubbleDown when largest element != current 
		swap(_heap[index], _heap[temp]);
		_bubbleDown(temp);
	}
}


template <class T>
void Heap<T>::insert(T item) {
	_heap[_n] = item; //adds the last item
	_n++; 
	_bubbleUp(_n - 1); //bubble
}

template <class T>
T Heap<T>::extractMax() {
	T max = _heap[0];
	_heap[0] = _heap[_n - 1];
	_n--;
	_bubbleDown(0);
	return max;
}


template <class T>
void Heap<T>::printHeapArray() {
	for (int i = 0; i < _n; i++)
		cout << _heap[i] << " ";
	cout << endl;
}

template <class T>
int Heap<T>::_lookFor(T x){ // not a very good implementation, but just use this for now.
    int i;
	for (i = 0;i < _n;i++) {
		if (_heap[i] == x) {
			return i;
		}
	}
    return -1;
}

template <class T>
void Heap<T>::decreaseKey(T from, T to) {
	int index = _lookFor(from);

	if (index == -1) {
		cout << "Item not found in heap." << endl;
		return;
	}

	_heap[index] = to; //updates from -> to
	_bubbleDown(index);
}


template <class T>
void Heap<T>::increaseKey(T from, T to) {
	int index = _lookFor(from);

	if (index == -1) {
		cout << "Item not found in heap." << endl;
		return;
	}

	_heap[index] = to; //updates from -> to
	_bubbleUp(index);
}

template <class T>
void Heap<T>::deleteItem(T x) {
	int index = _lookFor(x);

	if (index == -1) {
		cout << "Item not found in heap." << endl;
		return;
	}

	_heap[index] = _heap[_n - 1]; //swap n resize, then bubble
	_n--;
	if (_heap[(index - 1) / 2] < _heap[index]) {
		_bubbleUp(index); //if current > parent, bubbleup
	}
	_bubbleDown(index);
}

template <class T>
void Heap<T>::printTree() {
    int parity = 0;
	if (_n == 0)
		return;
	int space = pow(2,1 + (int) log2f(_n)),i;
	int nLevel = (int) log2f(_n)+1;
	int index = 0,endIndex;
    int tempIndex;
	
	for (int l = 0; l < nLevel; l++)
	{
		index = 1;
        parity = 0;
		for (i = 0; i < l; i++)
			index *= 2;
		endIndex = index * 2 - 1;
		index--;
        tempIndex = index;
        while (index < _n && index < endIndex) {
            for (i = 0; i < space-1; i++)
                cout << " ";
            if(index==0)
                cout << "|";
            else if (parity)
                cout << "\\";
            else
                cout << "/";
            parity = ~parity;
            for (i = 0; i < space; i++)
                cout << " ";
			index++;
		}
        cout << endl;
        index=tempIndex;
		while (index < _n && index < endIndex) {
			for (i = 0; i < (space-1-((int) log10(_heap[index]))); i++)
				cout << " ";
			cout << _heap[index];
			for (i = 0; i < space; i++)
				cout << " ";
			index++;
		}
		
		cout << endl;
		space /= 2;
	}

}






#endif
