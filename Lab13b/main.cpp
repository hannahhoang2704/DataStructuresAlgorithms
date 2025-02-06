#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "Item.h"

using namespace std;

void read_file(const string file_path, int &number, int&capacity, vector<Item> &items_container);
int main() {
    const string file_path = "/Users/HannahHoang/DataStructure/Lab13/hard33.txt";
    int number, capacity;
    vector<Item> items;
    read_file(file_path, number, capacity, items);

    sort(items.begin(), items.end(), [](Item &item_a, Item &item_b ){
        return ((double)item_a.value_get()/item_a.weight_get()) > ((double)item_b.value_get()/item_b.weight_get());
    });

    int best_weight = 0;
    int best_value = 0;
    vector<Item> best_combo;
    for (int i = 0; i < items.size(); i++ ){
        if (best_weight + items[i].weight_get() <= capacity){
            best_combo.push_back(items[i]);
            best_value += items[i].value_get();
            best_weight += items[i].weight_get();
        }
    }

    cout << "Feasible solution (not necessary optimal) found: " << "<" << best_value << "> " << "<" << best_weight << ">" << endl;
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