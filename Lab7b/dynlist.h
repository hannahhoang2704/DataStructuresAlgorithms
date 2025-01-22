/* dynlist.h -- Dynamic linked linear list */
#include <iostream>
using namespace std;
// Interface of list
template <class T>
class LinkedList {
private:
	// definition of the list node class
	class Node {
	public:
		T     _value;	// data
		Node *_pNext;	// pointer to the next node
		Node() : _pNext(NULL) {}
		Node(T val) : _value(val), _pNext(NULL) {}
		Node(T val, Node* next) : _value(val), _pNext(next) {}
	};

	Node *first;
    int _size;
public:
	LinkedList();
	~LinkedList();
	LinkedList<T>& insert_to_end(T data);
    LinkedList<T>& insert_to_begin(T data);
    void delete_first();
    void delete_last();
    void del(int idx);
    bool find_pos(T item, int &pos);
    bool insert(T item);
    int size();
    T& operator[](int position);
	void print(std::ostream &out = std::cout) const;
};

// Implementation of list
template <class T>
LinkedList<T>::LinkedList() {
    first = NULL;
    _size = 0;
}

template <class T>
LinkedList<T>::~LinkedList() {
    Node *aux1, *aux2;

    aux1 = first;
    while (aux1 != NULL) {
	    aux2 = aux1->_pNext;
	    delete aux1;
	    printf("\nDeleted"); //for testing purposes
	    aux1 = aux2;
    }
}

template <class T>
LinkedList<T>& LinkedList<T>::insert_to_end(T data) {
    Node *newnode = new Node(data);
    if (first == NULL)
	    first = newnode;		//first node
    else{
        Node *next_node = first;
        while (next_node->_pNext != NULL){
            next_node = next_node->_pNext;
        }
        next_node ->_pNext = newnode;
    }
    _size++;
	return *this;
}

template <class T>
LinkedList<T>& LinkedList<T>::insert_to_begin(T data) {
    Node *newnode = new Node(data);
    if (first == NULL)
        first = newnode;
    else{
        Node *next_node = first;
        first = newnode;
        first->_pNext = next_node;
    }
    _size++;
    return *this;
}

template <class T>
void LinkedList<T>::print(std::ostream &out) const {
    Node *what;

    out << "\nList:";
    what = first;
    while (what != NULL) {
	    out << " " << what->_value << " ";
	    what = what->_pNext;
    }
	out << endl;
}

template <class T>
std::ostream &operator<<(std::ostream &out,  LinkedList<T> const &data) {
	data.print(out);
	return out;
}

template <class T>
void LinkedList<T>::delete_first(){
    if (first != NULL){
        Node *next_node = first->_pNext;
        Node *first_node = first;
        first = next_node;
        delete first_node;
        _size--;
    }
}

template <class T>
void LinkedList<T>::delete_last() {
    Node *next_node1, *next_node2;
    if (first!=NULL){
        next_node1 = first;
        next_node2 = first->_pNext;
        if (next_node1->_pNext == NULL){
            delete first;
            first = NULL;
        }else{
            while (next_node2->_pNext != NULL){
                next_node1 = next_node2;
                next_node2 = next_node2->_pNext;
            }
            next_node1->_pNext = NULL;
            delete next_node2;
        }
        _size--;
    }
}

template <class T>
bool LinkedList<T>::find_pos(T item, int &pos) {
    Node *what;
    bool found = false;
    int idx = 0;
    what = first;
    while (what != NULL){
        if (what->_value == item){
            pos = idx;
            found = true;
            break;
        }
        what = what->_pNext;
        idx++;
    }
    return found;
}

template <class T>
int LinkedList<T>::size(){
//    cout << "size: " << _size << endl;
    return _size;
}


template <class T>
bool LinkedList<T>::insert(T item) {
    if(_size==0){
        insert_to_end(item);
    }else{
        Node *prev, *current;
        prev = nullptr;
        current = first;
        while (current != NULL && current->_value < item){
            prev = current;
            current = current ->_pNext;
        }
        if (prev == nullptr){
            //first is bigger than item
            insert_to_begin(item);
        }else{
            Node *newnode = new Node(item);
            newnode->_pNext = current;
            prev->_pNext = newnode;
            _size++;
        }
    }
    return true;
}

template <class T>
T& LinkedList<T>::operator[](int position) {
    Node *node;
    node = first;
    int idx = 0;
    while(node != NULL && idx != position){
        node = node->_pNext;
        idx++;
    }
    return node->_value;
}

template <class T>
void LinkedList<T>::del(int idx) {
    if(idx < _size && idx >= 0){
        if(idx == 0){
            delete_first();
        }else if (idx == _size-1){
            delete_last();
        }else{
            Node *prev, *current;
            prev = nullptr;
            current = first;
            int i = 0;
            while(current != NULL && i != idx){
                prev = current;
                current = current->_pNext;
                i++;
            }
            if (prev != NULL && current != NULL){
                prev->_pNext = current->_pNext;
                delete current;
                _size--;
            }
        }
    }
}