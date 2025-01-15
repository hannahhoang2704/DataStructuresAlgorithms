#include <iostream>
#include "time.h"
#include "list.h"

using namespace std;

//Application
int main () {
     List<Time> list;
	 Time       item;
     int        i = 0;

	 cout << "Enter items? ";
     cin >> item;
     while (!(item == Time(0, 0))) {
         list.insert(item);
         //list.insert_to_begin(item);
		// list.insert_to_end(item);
         cin >> item;
     }
     //Print the contents of the list
     for (i = 1; i <= list.size(); i++)
		 cout << "\n " << i << "th item was " << list[i];
     cout << "\nDelete list items ?";
     cin >> item;
     while (!(item == Time(0, 0))) {
         if(list.find_pos(item, &i)) {
             cout << "\nThe position of the item in list is " << i << endl;
             list.del(i);
         } else
             cout << "\nItem not found";
             cin >> item;
         }
     //Print the contents of the list
     for (i = 1; i <= list.size(); i++)
         cout << "\n " << i << "th item was " << list[i];
	 cout << endl;

	 return 0;
}
