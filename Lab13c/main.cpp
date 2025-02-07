#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "Item.h"

using namespace std;

void read_file(const string file_path, int &number, int&capacity, vector<Item> &items_container);
void greedy(int &best_weight, int &best_value, vector<Item> &best_combo, const vector<Item>items, const int capacity);

int main() {
    const string file_path = "/Users/HannahHoang/DataStructure/Lab13/hard33.txt";
    int number, capacity;
    vector<Item> items;
    read_file(file_path, number, capacity, items);

    sort(items.begin(), items.end(), [](Item &item_a, Item &item_b ){
        return ((double)item_a.value_get()/item_a.weight_get()) > ((double)item_b.value_get()/item_b.weight_get());
    });

    int greedy_optimal_weight = 0;
    int greedy_optimal_value = 0;
    vector<Item> greedy_optimal_combo;
    greedy(greedy_optimal_weight, greedy_optimal_value, greedy_optimal_combo, items, capacity);

    int heuristic_best_val = 0;
    int heuristic_best_weight = 0;
    vector<Item> heuristic_best_combo;
    for (int i = 0; i < items.size(); i++){

        vector<Item> current_combo;
        int current_val =0;
        int current_weight = 0;
        current_combo.push_back(items[i]);
        current_val += items[i].value_get();
        current_weight += items[i].weight_get();
        for(int j= 0; j <items.size(); j++){
            if (i==j){
                continue;
            }
            if (current_weight + items[j].weight_get()<= capacity){
                current_combo.push_back(items[j]);
                current_val += items[j].value_get();
                current_weight += items[j].weight_get();
            }
        }
        if(current_weight > heuristic_best_weight & current_weight < capacity){
            heuristic_best_weight = current_weight;
            heuristic_best_val = current_val;
            heuristic_best_combo = current_combo;
        }
    }

    cout << "Feasible solution (heuristic seed optimal) found: " << "<" << heuristic_best_val << "> " << "<" << heuristic_best_weight << ">" << endl;
    for(Item item: heuristic_best_combo){
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

void greedy(int &best_weight, int &best_value, vector<Item> &best_combo, const vector<Item>items, const int capacity){
    for (int i = 0; i < items.size(); i++ ){
        if (best_weight + items[i].weight_get() <= capacity){
            best_combo.push_back(items[i]);
            best_value += items[i].value_get();
            best_weight += items[i].weight_get();
        }
    }
}