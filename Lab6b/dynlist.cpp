/* dynlist.cpp -- Dynamic linked linear list */

#include <iostream>

#include "dynlist.h"
#include "NodeData.h"
using namespace std;

// Application
int main (void)  {
    LinkedList<NodeData *> list;
    list.insert_to_end(new String("First complex number")).insert_to_end(new Complex(1, 3));
    list.insert_to_end(new String("Second complex number")).insert_to_end(new Complex(5, 9));
    list.print();
}
