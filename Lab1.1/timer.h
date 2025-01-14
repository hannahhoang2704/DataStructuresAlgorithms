//
// Created by Hanh Hoang on 13.1.2025.
//

#ifndef LAB1_TIMER_H
#define LAB1_TIMER_H
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

class Time {
public:
    void read(const std::string &prompt);
    bool lessThan(const Time &t) const;
    Time subtract(const Time &t) const;
    void display() const;

private:
    int hours, minutes;
};
#endif //LAB1_TIMER_H
