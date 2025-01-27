#include <iostream>
#include <vector>
#include <algorithm>
#define SIZE 7
#define MAX 37
#define MIN 1

using namespace std;
//Ordinary function
int randGen_1() {
    return rand() % 10 + 1;
}
//Function object
class RandGen_2 {
public:
    RandGen_2(int max, int min): max(max), min(min), numbers() {
        srand(time(NULL));
    }
    int operator()();
private:
    vector<int> numbers;
    int max;
    int min;
};

void print_number(int nr){
    static int i = 1;
    cout << "#"  <<  i << ": " << nr << endl;
    i++;
}
class Print{
public:
    Print(){
        idx = 1;
    };
    void operator()(int nr) {
        cout << "#"  <<  idx<< ": " << nr << endl;
        idx++;
    }
private:
    int idx;
};
int main(void) {
    vector<int> lotto1(SIZE);
    vector<int> lotto2(SIZE);

//this is how to use "ordinary"function
/* srand(time(NULL)); // it is necessary to remember to call this
generate(numbers.begin(), numbers.end(), randGen_1); */
//this is how to use function object
    RandGen_2 randGen_2(MAX, MIN);
    generate(lotto1.begin(), lotto1.end(), randGen_2);
    generate(lotto2.begin(), lotto2.end(), randGen_2);
    cout << "First lotto row: ";
    copy(lotto1.begin(), lotto1.end(), ostream_iterator<int>(cout , "  "));
    cout << endl;
    cout << "Second lotto row: ";
    copy(lotto2.begin(), lotto2.end(), ostream_iterator<int>(cout , "  "));
    cout << endl;
    sort(lotto1.begin(), lotto1.end());
    sort(lotto2.begin(), lotto2.end());
    vector<int> intersection;
    set_intersection(lotto1.begin(), lotto1.end(), lotto2.begin(), lotto2.end(), back_inserter(intersection));
    sort(intersection.begin(), intersection.end());
    Print print;
//    for_each(intersection.begin(), intersection.end(), print_number);
    for_each(intersection.begin(), intersection.end(), print);

    return EXIT_SUCCESS;
}


int RandGen_2::operator()() {
    int number;
    do {
        number = rand() %  (max - min +1) + min;
    } while(find(numbers.begin(), numbers.end(), number) != numbers.end());
    numbers.push_back(number);
    return number;
}