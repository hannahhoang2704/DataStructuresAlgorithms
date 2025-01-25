/* standard array queue implementation */
#include <iostream>

using namespace std;

// The interface of circular array  queue
#define MAXN 100000
template <class T>
class Queue {
private:
//    T   array[MAXN];
    T *array;
    int number_of_items;
    int current_length;

public:
    Queue();
    Queue(const Queue& q0);
    ~Queue();
    bool enqueue(T item);
    bool dequeue(T &item);
    void print();
};

// The implementation of queue
template <class T>
Queue<T>::Queue() {
    number_of_items = 0;
    current_length = MAXN;
    array = new T[current_length];
}

template <class T>
Queue<T>::~Queue() {
    delete[] array;
}

template <class T>
bool Queue<T>::enqueue(T item) {
    if (number_of_items >= current_length){
        current_length = current_length + MAXN;
        T *new_arr = new T[current_length];
        for(int i= 0; i< current_length; i++){
            new_arr[i] = array[i];
        }

        // delete the old array from memory
        delete[] array;
        array = new_arr;
        array[number_of_items++] = item;
//        cout << "size is increased and is now " << number_of_items <<" items" << endl;
        return true;
    }
    else {
        array[number_of_items++] = item;
        return (true);
    }
}

template <class T>
bool Queue<T>::dequeue(T &item) {
    int i;

    if (number_of_items == 0)
        return(false);
    else {
        item = array[0];
        for (i = 0; i < number_of_items-1; i++)
            array[i] = array[i+1];
        number_of_items--;
        return (true);
    }
}

template <class T>
void Queue<T>::print() {
    int i, n;
    cout << "\nQueue now: \n\n";
    for (i = 0; i < number_of_items; i++ ) {
        cout << " " << array[i] << "";
    }
    cout << "\n\n";
}
