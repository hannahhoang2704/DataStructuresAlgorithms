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
        Node *_pPrev;
        Node() : _pNext(NULL), _pPrev(NULL) {};
        Node(T val) : _value(val), _pNext(NULL), _pPrev(NULL) {};
        Node(T val, Node* next, Node* prev) : _value(val), _pNext(next), _pPrev(prev) {};
    };

    Node *first;
    Node *last;
    int _size;
public:
    LinkedList();
    ~LinkedList();
    LinkedList<T>& insert_to_back(T data);
    LinkedList<T>& insert_to_front(T data);
    int size();
    T& operator[](int position);
    void print(std::ostream &out = std::cout) const;
    void print_reverse(std::ostream &out = std::cout) const;
};

// Implementation of list
template <class T>
LinkedList<T>::LinkedList() {
    first = NULL;
    last = NULL;
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
LinkedList<T>& LinkedList<T>::insert_to_back(T data) {
    Node *newnode = new Node(data);
    if (first == NULL){
        first = newnode;		//first node
        last = newnode;
    }
    else{
        Node *last_node = last;
        last_node->_pNext = newnode;
        newnode->_pPrev = last_node;
        last = newnode;
    }
    _size++;
    return *this;
}

template <class T>
LinkedList<T>& LinkedList<T>::insert_to_front(T data) {
    Node *newnode = new Node(data);
    if (first == NULL){
        first = newnode;
        last = newnode;
    }
    else{
        Node *next_node = first;
        newnode->_pNext = next_node;
        next_node ->_pPrev = newnode;
        first = newnode;
    }
    _size++;
    return *this;
}

template <class T>
void LinkedList<T>::print(std::ostream &out) const {
    Node *what;

    out << "\nList: ";
    what = first;
    while (what != NULL) {
        out << " " << what->_value << " ";
        what = what->_pNext;
    }
}

template <class T>
std::ostream &operator<<(std::ostream &out,  LinkedList<T> const &data) {
    data.print(out);
    return out;
}

template <class T>
int LinkedList<T>::size(){
    return _size;
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
void LinkedList<T>::print_reverse(std::ostream &out) const {
    Node *node;
    node = last;
    out << "\nList: ";
    while (node !=NULL){
        out << node ->_value << " ";
        node = node->_pPrev;
    }
}