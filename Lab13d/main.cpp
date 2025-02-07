#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <thread>
#include <mutex>
#include "Item.h"

using namespace std;
void brute_force(int capacity, int number, int low_range, int max_range, int &best_value, int &best_weight, vector<Item> &best_combo, vector<Item>items);
void read_file(const string file_path, int &number, int&capacity, vector<Item> &items_container);
mutex mtx;
int main() {
    const string file_path = "/Users/HannahHoang/DataStructure/Lab13/easy20.txt";
    int number, capacity;
    vector<Item> items;
    read_file(file_path, number, capacity, items);
    uint64_t combination = pow(2,number);
    cout << combination << endl;
    int best_value = 0;
    int best_weight = 0;
    vector<Item> best_combo;
    auto processor_nr = thread::hardware_concurrency();
    vector<thread> threads;
    auto range_size =combination/processor_nr;
    for(int i = 0; i < processor_nr; i++){
        auto min_range = i * range_size;
        auto max_range = (i == processor_nr-1)? combination: (i+1)*range_size;
//        threads[i] = thread(brute_force, capacity, number, min_range, max_range, ref(best_value), ref(best_weight), ref(best_combo), items);
        threads.push_back(thread(brute_force, capacity, number, min_range, max_range, ref(best_value), ref(best_weight), ref(best_combo), items));

    }


    for (auto &thread:threads){
            thread.join();
    }

    cout << "Optimal solution found: " << "<" << best_value << "> " << "<" << best_weight << ">" << endl;
    for(Item item: best_combo){
        cout << "<" <<  item.index_get() << ">";
    }
    cout << endl;
    return EXIT_SUCCESS;
}


void brute_force(int capacity,  int number,  int low_range, int max_range, int &best_value, int &best_weight, vector<Item> &best_combo, vector<Item>items){
    for(uint64_t candidate =low_range; candidate <max_range; candidate++){
        vector<Item> current_combo;
        int current_val = 0;
        int current_weight =0;
        for(int i = 0; i < number; i++){
            if(candidate & (1 <<  i)){
                current_combo.push_back(items[i]);
                current_val += items[i].value_get();
                current_weight += items[i].weight_get();
            }
        }
        if(current_weight <= capacity && current_val > best_value){
            lock_guard<mutex> lock(mtx);
            best_value = current_val;
            best_weight = current_weight;
            best_combo = current_combo;
        }
    }
}


void read_file(const string file_path, int &number, int&capacity, vector<Item> &items_container){
    ifstream file;
    file.open(file_path);
    if (!file) cerr << "Error opening file: " << strerror(errno) << endl;
    if (file.is_open()) {
        file >> number;
        cout << "Total number: "<< number << endl;

        for(int i = 0; i < number; i++){
            Item item;
            file >> item;
            items_container.push_back(item);
        }
        file >> capacity;
        cout << "Total capacity: "<< capacity << endl;
        file.close();
    }

}