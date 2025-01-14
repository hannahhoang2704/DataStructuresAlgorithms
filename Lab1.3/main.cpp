//Exercise 1c
#include <iostream>
#include "timer.h"
#define MAX_RUNNER 10
using namespace std;
int main() {
    Time runner_time[MAX_RUNNER];
    cout << "How many times you have? ";
    int times_nr;
    cin >> times_nr;
    while (times_nr > MAX_RUNNER){
        cout << "Maximum time runner is " << MAX_RUNNER << " times. Input the times: " << endl;
        cin >> times_nr;
    }
    for (int i = 0; i < times_nr; i++){
       cout << "Give the time " << i + 1 << " (hh mm) ? ";
       cin >> runner_time[i];
    }
    Time smallest_time = runner_time[0];
    for (int i = 1; i < times_nr; i++){
        if (runner_time[i] < smallest_time){
            smallest_time = runner_time[i];
        }
    }
    cout << "Result list:" << endl;
    for (int i = 0; i < times_nr; i++){
        Time difference = runner_time[i] - smallest_time;
        cout << i+1 << ": " << runner_time[i] << " " << difference << endl;
    }

    return 0;
}
