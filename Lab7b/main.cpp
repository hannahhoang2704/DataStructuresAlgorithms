#include <iostream>
#include "dynlist.h"
#include "time.h"

using namespace std;
int main() {
    LinkedList<Time> list;
    Time       item;
    int        i = 0;

    cout << "Enter items? ";
    cin >> item;
    while (!(item == Time(0, 0))) {
        list.insert(item);
//        list.insert_to_begin(item);
        // list.insert_to_end(item);
        cin >> item;
    }
    //Print the contents of the list
    for (i = 0; i < list.size(); i++){
        cout << "\n " << i+1 << "th item was " << list[i];
    }
    cout << "\nDelete list items ?";
    cin >> item;
    while (!(item == Time(0, 0))) {
        if(list.find_pos(item, i)) {
            cout << "\nThe position of the item in list is " << i << endl;
            list.del(i);
        } else
            cout << "\nItem not found";
        cin >> item;
    }
    //Print the contents of the list
    for (i = 0; i < list.size(); i++)
        cout << "\n " << i+1 << "th item was " << list[i];
    cout << endl;

    return 0;
}
