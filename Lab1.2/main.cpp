//Exercise 1b
#include <iostream>
#include "timer.h"

using namespace std;
int main() {
    Time start, end, duration;
    cout << "Enter starting time ";
    cin >> start;
    cout << "Enter ending time ";
    cin >> end;
    duration = start < end ? end - start : start - end;
    cout << "Duration " << duration << endl;
    cout << "Starting time was " << end - duration << endl;
    cout << "Ending time was " << start + duration << endl;
    return 0;
}
