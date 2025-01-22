#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>
#include "time.h"

using namespace std;
int main() {
    Time item;
    vector<Time> container;
    cout << "Enter times (terminate with 0 0):?" <<endl;
    cin >> item;
    while(!(item == Time(0,0))){
        container.push_back(item);
        cin >> item;
    }
    cout << "Unsort times: " << endl;
    for (const auto &time:container){
        cout << time << endl;
    }
    cout << "Sorted times:" << endl;
    sort(container.begin(), container.end(), [](Time a, Time b){return a < b;});
    for (const auto &time:container){
        cout << time << endl;
    }
    cout << "Time differences: " << endl;
    vector<Time> different_time;
    adjacent_difference(container.begin(), container.end(), back_inserter(different_time));
    for(int i = 0; i < container.size(); i++){
        cout << container[i] << "  " << different_time[i] << endl;
    }

    return 0;
}
