//
// Created by Hanh Hoang on 14.1.2025.
//
#include "measurement.h"

using namespace std;

Measurements::Measurements() : value_stores(nullptr), count(0) {}

Measurements::~Measurements(){
    delete[] value_stores;
}

Measurements& Measurements::operator=(const Measurements& other) {
    if (this == &other) {
        return *this;
    }

    if(value_stores != nullptr){
        delete[] value_stores;
    }
    count = other.count;
    if (count > 0) {
        value_stores = new double[count];
        memcpy(value_stores, other.value_stores, count * sizeof(double));
    } else {
        value_stores = nullptr;
    }
    return *this;
}

bool Measurements::read(const char *filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Can't open the file";
        return false;
    }
    file >> count;
    value_stores = new double [count];
    for(int i = 0; i < count; i++){
        file >> value_stores[i];
    }
    file.close();
    return true;
}

void Measurements::print() const {
    for(int i= 0; i < count; i++){
        cout << value_stores[i] << endl;
    }
}

double Measurements::mean(){
    double sum = 0.0;
    for (int i = 0; i < count; i++){
        sum += value_stores[i];
    }
    return sum/count;
}

void Measurements::inc(double increment) {
    for (int i = 0; i < count; i++){
        value_stores[i] = value_stores[i] + increment;
    }
}