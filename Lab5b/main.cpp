/* simple test program to test the queue implementation */
#include <iostream>
//#include "queue.h"
#include "circ_arr.h"
#include <stdlib.h>
#include <time.h>

#define N 100000 // number of elements inserted/retrieved from the queue, must be even
//#define N 100 // number of elements inserted/retrieved from the queue, must be even
using namespace std;


// Application
int main() {
    Queue<int> queue;
    int item;
    clock_t tic, tac;
    double duration;
    int i;

    // first we play a little with the queue to test that it really works
    cout << "Fill the queue with " << N << " items\n";
    item = 0;
    for (i = 0; i < N; i++) {
        if (!queue.enqueue(item++)) {
            cerr << "Enqueue failed\n";
            exit(1);
        }
    }
    queue.print();
    cout << "Remove half of them\n";
    for (i = 0; i < N/2; i++) {
        if (!queue.dequeue(item)) {
            cerr << "Dequeue failed\n";
            exit(1);
        }
    }
    queue.print();

    cout << "Add then new " << N/2 << " items to the queue\n";
    item++;
    for (i = 0; i < N/2; i++) {
        if (!queue.enqueue(item++)) {
            cerr << "Enqueue failed\n";
            exit(1);
        }
    }
    queue.print();

    // then we deque elements and measure the execution time
    cout << "Then dequeue them\n";
    tic = clock();
    for (i = 0; i < N; i++)
        queue.dequeue(item);
    tac = clock();
    cout << "Last item value " << item << " (should be " << N-1 << ")\n";
    cout << "(tic " << tic << ", tac " << tac << ")\n";
    duration = (double)(tac - tic) / CLOCKS_PER_SEC;
    cout << "\ndequeue took " << duration / (double)N*1e6 << " us to run\n";

	return 0;
}
