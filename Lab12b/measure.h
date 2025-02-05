//
// Created by Hanh Hoang on 4.2.2025.
//

#ifndef LAB12B_MEASURE_H
#define LAB12B_MEASURE_H
#include <iostream>
#include <complex>
#include <future>
#include <chrono>
#include <numeric>
#include <vector>

using namespace std;

typedef complex<double> cx;

class Measure{
public:
    explicit Measure(int run_times=30, int remove_element=10): run_times(run_times), remove_element(remove_element){};
    ~Measure()=default;
    virtual void run()=0;
    virtual void measure(double &mean, double &stdev);

private:
    int run_times=30;
    int remove_element=10;
    vector<long long> time_container;
};

class FFTTestbed: public Measure{
public:
    FFTTestbed(void (*func)(int, cx[]), int nr ): Measure(), m_function(func),  number(nr){
        input = new cx[nr];
        for(int i = 0; i < nr; i++){
            input[i] = cx(i,-i);
        }
    };
    ~FFTTestbed(){
        delete[] input;
    };
private:
    void run() override{
        m_function(number, input);
    };
    void (*m_function)(int, cx[]);
    int number;
    cx *input;
};

void Measure::measure(double &mean, double &stdev){
    for (int j= 0; j < run_times; j++){
        chrono::time_point<chrono::high_resolution_clock> start = chrono::high_resolution_clock::now();
        run();
        chrono::time_point<chrono::high_resolution_clock> end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds> (end-start).count();
        time_container.push_back(duration);
    }
    sort(time_container.begin(), time_container.end());
    time_container.erase(time_container.begin() + remove_element, time_container.end());
    mean = accumulate(time_container.begin(), time_container.end(),0.0)/time_container.size();
    auto accum = 0;
    for_each(time_container.begin(), time_container.end(), [&](long long &duration){
        accum += (duration-mean)*(duration-mean);
    });
    stdev = sqrt(accum/(time_container.size()-1));
}
#endif //LAB12B_MEASURE_H
