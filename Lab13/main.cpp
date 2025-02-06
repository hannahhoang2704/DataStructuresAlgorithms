#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "Item.h"

using namespace std;

void read_file(const string file_path, int &number, int&capacity, vector<Item> &items_container);
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
    for(uint64_t candidate =0; candidate <combination; candidate++){
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
            best_value = current_val;
            best_weight = current_weight;
            best_combo = current_combo;
        }
        if(candidate % 1000000 == 0){
            double progress = ((double) candidate/(double)combination)*100;
            cout << (int)progress << "%" << endl;
        }else if (candidate == combination-1){
            cout << "100%" << endl;
        }
    }

    cout << "Optimal solution found: " << "<" << best_value << "> " << "<" << best_weight << ">" << endl;
    for(Item item: best_combo){
        cout << "<" <<  item.index_get() << ">";
    }
    cout << endl;
    return EXIT_SUCCESS;
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