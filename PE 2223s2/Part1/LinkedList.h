

#include <iostream>
using namespace std;

#define SPLITSTR "Splitting: "
#define INTOSTR "Into :"
#define MERGESTR "Merging: "


class ListNode {

private:
    int _item;
    ListNode* _next;

public:
    ListNode( int );        // Constructs the list node with parameter
    void printItem();       // Prints the item

    friend class List;
};

class List {

private:
    ListNode* _head;
    int _size;

public:
    List();                             // Constructs an empty list
    ~List();                            // Destructs a list

    void insertHead( int );             // Inserts the new value into the linked list
    int getHeadItem();                  // Retrieves the value in the head node
    int removeHead();                   // Removes the head node and returns the value removed

    void bubbleSort();            // TODO: Implement bubble sort
    void mergeSort();                   // Calls the recursive merge sort function

    void split( List* );                // TODO: Splits the linked lists into two halves
    void merge( List* );                // TODO: Merge two linked lists in ascending order

    void print();                 // Prints all items of the linked lists.
};








/*
 * LISTNODE CONSTRUCTUORS AND FUNCTIONS
 */
ListNode::ListNode(int item) {
    _item = item;
    _next = NULL;
}

void ListNode::printItem() {
    cout << _item;
}


/*
 * LIST CONSTRUCTORS AND FUNCTIONS
 */
List::List() {
    _head = NULL;
    _size = 0;
}

List::~List() {
    while (_head) {
        removeHead();
    }
}

void List::insertHead(int item) {
    ListNode* newNode = new ListNode(item);
    newNode->_next = _head;
    _head = newNode;
    _size++;
}

int List::getHeadItem() {
    return _head->_item;
}

int List::removeHead() {
    int item = -32768;  
    ListNode* temp;

    if (_head) {
        temp = _head;
        item = getHeadItem();
        _head = _head->_next;
        delete temp;
        _size--;
    }

    return item;
}

void List::bubbleSort() {

    // TODO: Implement bubble sort on this implementation of single linked list.
    //       Print the linked list after every pass in the outer iteration
    //       using print(false) function in List class if parameter is true.
    //       The list should be sorted in ascending order.

    // ENTER YOUR ANSWER BELOW.
    ListNode* last = nullptr;
    bool swapped = true;

    if (_size <= 1)
        return;

    while (swapped) {
        swapped = false;
        ListNode* curr = _head;
        while (curr != last && curr->_next != nullptr) { //while(2 indexes are not NULL)
            if (curr->_item > curr->_next->_item) {
                swap(curr->_item, curr->_next->_item);
                swapped = true;
            }
            curr = curr->_next;
        }
        last = curr;
        if (!swapped) {
            break;
        }
        print(); //print after each bubble
        
    }
    // ENTER YOUR ANSWER ABOVE.
}

void List::mergeSort() {
    List rightHalf;
    List leftHalf;
    if (_size <= 1) {
        return;
    }
    // modify this function
    // 
    // each time you split a list
    cout << SPLITSTR;
    // original unsplitted list print
    print();
    cout << INTOSTR << endl;
    // original splitted list print (but it's halved)
    // the other splitted list print
    split(&leftHalf);
    print();
    leftHalf.print();
    mergeSort();
    leftHalf.mergeSort();
    // after you sorted the two lists
    cout << MERGESTR << endl;
    // original splitted list print (but it's halved)
    // the other splitted list print
    print();
    leftHalf.print();
    merge(&leftHalf);


    // after you merged the above two sorted lists
    cout << INTOSTR;
    // print the merged sorted single list
    print();
    leftHalf = rightHalf;
}
  


void List::split(List* otherList) {
    // TODO: Implement splitting of the current list.
    //       The first half of the list will be pointed by itself.
    //       The second half of the list will be pointed by otherList.
    //       It is guaranteed that the original list will have more than one node.
    //
    //       No need to print within split()
    
    // ENTER YOUR ANSWER BELOW.
    int half = _size / 2;
    ListNode* curr = _head;
    ListNode* prev = nullptr;

    for (int i = 0; i < half; i++) { //move through first half
        prev = curr; //keeptrack of prev
        curr = curr->_next; //advance curr
    }
    if (prev) {
        prev->_next = nullptr;//cut the link
    }
    otherList->_head = curr; //2nd half starts from curr
    
    otherList->_size = _size - half; //update size
    _size = half;
   // ENTER YOUR ANSWER ABOVE.
}

void List::merge(List* otherList) {
    // TODO: Implement merging of current list and otherList.
    //       The otherList should be empty after merging.
    //       It is guaranteed that both lists are non-empty.
    //
    //       No need to print within merge()
    // ENTER YOUR ANSWER BELOW.

    ListNode* mergedHead = nullptr;
    ListNode* mergedTail = nullptr;
    ListNode* curr1 = _head;
    ListNode* curr2 = otherList->_head;

    if (curr1->_item <= curr2->_item) {
        mergedHead = curr1;
        curr1 = curr1->_next;
    }
    else {
        mergedHead = curr2;
        curr2 = curr2->_next;
    }

    mergedTail = mergedHead;

    while (curr1 != nullptr && curr2 != nullptr) {
        if (curr1->_item <= curr2->_item) {
            mergedTail->_next = curr1;
            curr1 = curr1->_next;
        }
        else {
            mergedTail->_next = curr2;
            curr2 = curr2->_next;
        }
        mergedTail = mergedTail->_next;
    }

    if (curr1 != nullptr) {
        mergedTail->_next = curr1;
    }
    else if (curr2 != nullptr) {
        mergedTail->_next = curr2;
    }

    _head = mergedHead;
    _size += otherList->_size;
    otherList->_head = nullptr;
    otherList->_size = 0;

    // ENTER YOUR ANSWER ABOVE.
}

void List::print() {

    ListNode* curr = _head;

    while (curr) {
        cout << curr->_item;
        cout << " ";
        curr = curr->_next;
    }

    cout << endl;
}




