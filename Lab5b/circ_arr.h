#include <iostream>

using namespace std;

//#define MAXN 100000

template <class Titem>
class Queue {
private:
    Titem *array;
    int first;
    int last;
    int number_of_items;
    int capacity;
    void expand();
public:
    Queue();
    ~Queue();
    bool enqueue(Titem item);
    bool dequeue(Titem &item);
    void print();
};

template <class Titem>
Queue<Titem>::Queue() {
    capacity = 10;
    array = new Titem[capacity];
    first = 0;
    last = -1;
    number_of_items = 0;
}

template <class Titem>
Queue<Titem>::~Queue(){
    delete[] array;
}

template <class Titem>
void Queue<Titem>::expand() {
    int new_capacity = capacity*2;
    Titem *new_arr = new Titem[new_capacity];
    for(int i = 0; i < number_of_items; i++){
        new_arr[i] = array[(first+i) %capacity];
    }
    delete[] array;
    array = new_arr;
    capacity = new_capacity;
    first = 0;
    last = number_of_items-1;
}

template <class Titem>
bool Queue<Titem>::enqueue(Titem item) {
    if (number_of_items == capacity){
        expand();
    }

    last = (last+1)%capacity;
    array[last] = item;
    number_of_items++;

    return (true);
}
template <class Titem>
bool Queue<Titem>::dequeue(Titem &item) {
    if (number_of_items == 0)
        return(false);
    else {
        item = array[first];
        first = (first+1)%capacity;
        number_of_items--;
        return (true);
    }
}
template <class Titem>
void Queue<Titem>::print() {
    int i, n;
    cout << "\nQueue now: \n\n";
    for (n = 0, i=first; n < number_of_items ; n++) {
        cout << " " << array[i] << " ";
        i = (i+1)%capacity;
    }
    cout << endl << endl;
}