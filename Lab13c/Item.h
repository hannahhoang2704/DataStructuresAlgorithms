//
// Created by Hanh Hoang on 6.2.2025.
//

#ifndef LAB13_ITEM_H
#define LAB13_ITEM_H
#include <iostream>
#include <fstream>

using namespace  std;

class Item {
    friend ostream& operator<<(ostream &os, Item &item);
    friend istream& operator >>(istream &is, Item &item);
public:
    explicit Item(int index=0, int value=0, int weight=0): index(index), value(value), weight(weight){};
    ~Item() = default;
    int index_get() const { return index;}
    int value_get() const { return value;}
    int weight_get() const {return weight;}
private:
    int index;
    int value;
    int weight;
};

ostream& operator<<(ostream &os, Item &item){
    os << item.index << "\t" << item.value << endl;
    return os;
}


istream& operator >>(istream &is, Item &item){
    is >> item.index >> item.value >> item.weight;
    return is;
}

#endif //LAB13_ITEM_H
