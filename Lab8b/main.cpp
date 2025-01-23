#include <iostream>
#include "tbdl.h"

using namespace std;
int main() {
    LinkedList<int> dbl;
    dbl.print();
    dbl.print_reverse();
    dbl.insert_to_back(10);
    dbl.print();
    dbl.print_reverse();
    dbl.insert_to_front(20);
    dbl.print();
    dbl.print_reverse();
    dbl.insert_to_back(30);
    dbl.print();
    dbl.print_reverse();
    dbl.insert_to_front(40);
    dbl.print();
    dbl.print_reverse();
    dbl.insert_to_back(50);
    dbl.print();
    dbl.print_reverse();
    return EXIT_SUCCESS;
}
